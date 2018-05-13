#include "taskqueue.h"
#include "ui_taskqueue.h"

#include <QDebug>
#include <QSettings>

TaskQueue::TaskQueue(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::TaskQueue),
        compressor(new CompressorWrapper(this)),
        yd(new YDAPI(this))
{
    ui->setupUi(this);

    ui->treeWidget->setItemDelegateForColumn(1, new ProgressBarDelegate());
    ui->treeWidget->setItemDelegateForColumn(2, new ProgressBarDelegate());

    connect(compressor, &CompressorWrapper::onCompressDirSucces, this, [&](){
        completedOperations++;
        updateTotalProgressBar();

        upload();
    });

    connect(yd, &YDAPI::uploadFinished, this, [&](){
        completedOperations++;
        updateTotalProgressBar();

        currentOperation = nothing;
        disconnect(yd, &YDAPI::uploadProgress, 0, 0);
        start();
    });

    connect(compressor, &CompressorWrapper::onCompressError, this, &TaskQueue::onCompressingError);
    connect(yd, &YDAPI::onError, this, &TaskQueue::onUploadingError);

    this->init();
}

void TaskQueue::init()
{
    numberOfOperations = 0;
    completedOperations = 0;
    currentIndex = -1;
    currentOperation = nothing;

    ui->treeWidget->clear();
    taskList.clear();
    ui->totalProgressBar->setValue(0);
}

QString TaskQueue::genArchiveName(BackupTaskSpecs *task)
{
    QString archiveName = task->getPathTo() + QDir::separator() +
                    task->getName() + "_" + QDate::currentDate().toString("dd.MM.yyyy");

    qDebug() << archiveName;

    if( QFile(archiveName + ".zip").exists() ) {
        archiveName.append("(%1)");
        int index = 1;

        while( QFile(archiveName.arg(index) + ".zip").exists() )
            index++;

        archiveName = archiveName.arg(index);
    }

    archiveName.append(".zip");

    return archiveName;
}

void TaskQueue::addTask(BackupTaskSpecs *taskSpecs)
{
    QStringList itemText;
    itemText << taskSpecs->getName() << "0";
    QString token = QSettings().value("Token").toString();
    if(token != "" && taskSpecs->getUpload())
        itemText << "0";
    else
        itemText << "--";

    QPair<BackupTaskSpecs*, QTreeWidgetItem*> newTask;
    newTask.first  = taskSpecs;
    newTask.second = new QTreeWidgetItem(ui->treeWidget, itemText);

    taskList.append(newTask);

    numberOfOperations += ((taskSpecs->getUpload() && token!="") ? 2 : 1);
    //start();
}

TaskQueue::~TaskQueue()
{
    delete ui;
}

void TaskQueue::start()
{
    if(currentOperation != nothing) return;

    if(!taskList.empty()) {
        currentTask = taskList.takeFirst();
        compress();
    } else {
        currentTask.first = nullptr;
        currentTask.second = nullptr;
    }
}

void TaskQueue::compress()
{
    currentArchiveName = genArchiveName(currentTask.first);
    connect(compressor, &CompressorWrapper::compressProgress, [=](qint64 done, qint64 total){
        currentTask.second->setText(1, QString::number( (qint64)((100*done)/total) ));
    });

    currentOperation = compressing;
    compressor->compressDir(currentTask.first->getPathFrom(), currentArchiveName);
}

void TaskQueue::upload()
{
    QObject::disconnect(compressor, &CompressorWrapper::compressProgress, 0, 0);

    if(currentTask.first->getUpload() && QSettings().value("Token").toString() != "") {
        yd->setToken(QSettings().value("Token").toString());
        currentOperation = uploading;

        connect(yd, &YDAPI::uploadProgress, [=](qint64 done, qint64 total){
            if(total != 0)
                currentTask.second->setText(2, QString::number( (qint64)((100*done)/total) ));
        });
        yd->uploadToFolder(currentArchiveName, currentTask.first->getName());

    } else {
        currentOperation = nothing;
        start();
    }
}

void TaskQueue::stop()
{
    switch (currentOperation) {
    case compressing:
        disconnect(compressor, &CompressorWrapper::compressProgress, 0, 0);
        completedOperations--;
        updateTotalProgressBar();

        compressor->stop();
        currentTask.second->setText(1, "0");

        break;
    case uploading:
        disconnect(yd, &YDAPI::uploadProgress, 0, 0);
        completedOperations -= 2;
        updateTotalProgressBar();

        yd->stop();
        currentTask.second->setText(1, "0");
        currentTask.second->setText(2, "0");

        break;
    default:
        break;
    }
    taskList.push_front(currentTask);
    currentOperation = nothing;
}

void TaskQueue::clear()
{
    this->stop();
    this->init();
}

void TaskQueue::onCompressingError(QString message)
{
    currentTask.second->setText(1, message);
    completedOperations++;
    if(currentTask.first->getUpload()) {
        completedOperations++;
        currentTask.second->setText(2, "Error");
    }
    currentTask.first = nullptr;
    currentTask.second = nullptr;
    start();
}

void TaskQueue::onUploadingError(int code, QString message)
{
    if(code == 206) return;
    currentTask.second->setText(2, QString::number(code) + " " + message);
    completedOperations++;
    start();
}

void TaskQueue::updateTaskProgressBar(qint64 done, qint64 total)
{
    int column;

    if(currentOperation == compressing)
        column = 1;
    else if(currentOperation == uploading)
        column = 2;

    QString progress = QString::number( (qint64)((100*done)/total) );
    currentTask.second->setText(column, progress);
}

void TaskQueue::updateTotalProgressBar()
{
    ui->totalProgressBar->setValue((100 * (completedOperations/numberOfOperations)));
}

void TaskQueue::on_startButton_clicked()
{
    this->start();
}

void TaskQueue::on_stopButton_clicked()
{
    this->stop();
}

void TaskQueue::on_clearButton_clicked()
{
    this->clear();
}

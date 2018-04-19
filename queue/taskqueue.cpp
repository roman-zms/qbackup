#include "taskqueue.h"
#include "ui_taskqueue.h"

#include <QDebug>

TaskQueue::TaskQueue(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::TaskQueue),
        compressor(new CompressorWrapper())
{
    ui->setupUi(this);

    ui->treeWidget->setItemDelegateForColumn(1, new ProgressBarDelegate());
    ui->treeWidget->setItemDelegateForColumn(2, new ProgressBarDelegate());

    connect(compressor, SIGNAL(onCompressDirSucces()), this, SLOT(upload()));

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
    itemText << (taskSpecs->getUpload() ? "0" : "--");

    currentTask.first  = taskSpecs;
    currentTask.second = new QTreeWidgetItem(ui->treeWidget, itemText);

    taskList.append(currentTask);

    numberOfOperations += (taskSpecs->getUpload() ? 2 : 1);
}

TaskQueue::~TaskQueue()
{
    delete ui;
}

void TaskQueue::start()
{
    if(currentOperation != nothing) return;

    currentTask = taskList.takeFirst();
    compress();
}

void TaskQueue::compress()
{
    QString archiveName = genArchiveName(currentTask.first);
    connect(compressor, &CompressorWrapper::compressProgress, [=](qint64 done, qint64 total){
        currentTask.second->setText(1, QString::number( (qint64)((100*sent)/total) ));
    });

    compressor->compressDir(currentTask.first->getPathFrom(), archiveName);
}

void TaskQueue::upload()
{
    compressor->disconnect(&CompressorWrapper::compressProgress);
}

void TaskQueue::stop()
{
    switch (currentOperation) {
    case compressing:

        break;
    case uploading:

        break;
    default:
        break;
    }
    currentOperation = nothing;
}

void TaskQueue::clear()
{
    this->stop();
    this->init();
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

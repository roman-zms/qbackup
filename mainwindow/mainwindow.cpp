#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    taskQueue(new TaskQueue())
{
    ui->setupUi(this);
    loadAllTasks();

    taskQueue->hide();

    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
            this, 			SLOT(openTaskSettings(QTreeWidgetItem*)));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete taskQueue;
}

void MainWindow::on_actionAddTask_triggered()
{
    addNewTask();
}

void MainWindow::loadTask(QString name)
{
    if(!tasks.contains(name)){
        BackupTask *task = new BackupTask(name);
        tasks.insert(name, task);
    }

    BackupTask *task = tasks.value(name);
    if(task->specs->getAutoBackup())
        connect(task, &BackupTask::timeout, this, &MainWindow::onTaskTimeout, Qt::UniqueConnection);
    else
        disconnect(task, &BackupTask::timeout, this, &MainWindow::onTaskTimeout);

    QStringList taskSettings;
    taskSettings << task->specs->getName() << task->specs->getPathFrom() << task->specs->getPathTo();
    if(task->specs->getAutoBackup())
        taskSettings << getScheduleString(*(task->specs->getSchedule()));

    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget, taskSettings);
    ui->treeWidget->addTopLevelItem(item);
}

void MainWindow::onTaskTimeout()
{
    BackupTask *task = qobject_cast<BackupTask*>(sender());
    taskQueue->addTask(task->specs);
}

void MainWindow::addToQueue()
{
    if(ui->treeWidget->selectedItems().empty()) return;
    foreach (QTreeWidgetItem *item, ui->treeWidget->selectedItems()) {
        auto *spec = tasks.value(item->text(0))->specs;
        if(QDir(spec->getPathFrom()).exists() &&
                        QDir(spec->getPathTo()).exists()) {
            this->taskQueue->addTask(tasks.value(item->text(0))->specs);
        } else {
            QMessageBox::critical(this, "Error", "Invalid task");
        }
    }
}

void MainWindow::addNewTask()
{
    QString name;
    bool succes;

    do {
        name = QInputDialog::getText(
                this, tr("Name"),
                tr("Enter new backup name:"),
                QLineEdit::Normal,"",&succes);

        if(succes==false)
            return;

    } while(name.isEmpty());

    QString itemString = "";
    QTreeWidgetItem *item = new QTreeWidgetItem(
                ui->treeWidget, QString("").append(name + ",/path/from/,/path/to/").split(','));
    //item->setCheckState(0, Qt::CheckState::Unchecked);
    ui->treeWidget->addTopLevelItem(item);

    openTaskSettings(new BackupTask(name));
}

void MainWindow::removeTask()
{
    QList<QTreeWidgetItem*> items = ui->treeWidget->selectedItems();

    QSettings *settings = new QSettings(this);
    //settings->beginGroup("Tasks");

    foreach(QTreeWidgetItem *item, items){
        tasks.take(item->text(0))->deleteLater();
        settings->remove(item->text(0));
    }

    settings->deleteLater();

    loadAllTasks();
}

void MainWindow::openTaskSettings(QTreeWidgetItem *item)
{
    QString name = item->text(0);

    openTaskSettings(tasks.value(name));
}

void MainWindow::openTaskSettings(BackupTask *task)
{
    TaskSettings *taskSettings = new TaskSettings(task);

    connect(taskSettings, SIGNAL(finished(int)), taskSettings, SLOT(deleteLater()));
    connect(taskSettings, SIGNAL(accepted()), this, SLOT(loadAllTasks()));
    taskSettings->show();

}

void MainWindow::loadAllTasks()
{
    ui->treeWidget->clear();

    QSettings *settings = new QSettings(this);
    //settings->beginGroup("Tasks");

    QStringList taskNames = settings->childGroups();
    taskNames.removeOne("General");
    settings->deleteLater();

    foreach(QString taskName, taskNames) {
        loadTask(taskName);
    }
}

void MainWindow::on_actionRemoveTask_triggered()
{
    removeTask();
}

void MainWindow::on_actionShow_queue_triggered()
{
    taskQueue->show();
}

void MainWindow::on_actionRunBackup_triggered()
{
    on_actionAdd_to_queue_triggered();
    taskQueue->start();
}

void MainWindow::on_actionSettings_triggered()
{
    gSettings = new GeneralSettings(this);
    gSettings->show();
    connect(gSettings, &GeneralSettings::finished, gSettings, &GeneralSettings::deleteLater);
}

void MainWindow::on_actionAdd_to_queue_triggered()
{
    addToQueue();
}

QString MainWindow::getScheduleString(const TaskSchedule &schedule)
{
    if(schedule.getTime().isNull()) return "";
    QStringList daysOfWeek{
        tr("Mo"),
        tr("Tu"),
        tr("We"),
        tr("Th"),
        tr("Fr"),
        tr("Sa"),
        tr("Su")
    };
    QString string;
    QTextStream str(&string);
    str << schedule.getTime().toString("hh:mm") << " ";
    for(int i=0; i<7; i++) {
        if(schedule.containsDay(i+1)) {
            str << daysOfWeek.at(i) <<" ";
        }
    }
    return string;

}

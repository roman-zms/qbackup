#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <timedmessage/timedmessagebox.h>
#include <QProcess>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    //taskQueue(new TaskQueue()),
    nTaskQueue(new NTaskQueue(this)),
    TQForm(new TaskQueueForm(nTaskQueue)),
    tray(new QSystemTrayIcon(this))
{
    ui->setupUi(this);
    loadAllTasks();
    TQForm->hide();

    initTray();

    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
            this, 			SLOT(openTaskSettings(QTreeWidgetItem*)));

    connect(nTaskQueue, &NTaskQueue::shutdownCommand,
            this, &MainWindow::shutdownSystem);

}

MainWindow::~MainWindow()
{
    for(auto key : tasks.keys()) {
        tasks.take(key)->deleteLater();
    }

    delete ui;
}

void MainWindow::on_actionAddTask_triggered()
{
    addNewTask();
}

void MainWindow::loadTask(QString name)
{
    if (!tasks.contains(name)) {
        tasks.insert(name, new BackupTask(name));
    }

    BackupTask *task = tasks.value(name);

    scheduleBackup(task);
    addTaskItemToTree(ui->treeWidget, task);
}

void MainWindow::onTaskTimeout()
{
    BackupTask *task = qobject_cast<BackupTask*>(sender());

    qDebug() << "Timeout "
             << task->specs->getName();

    nTaskQueue->put(task);
    nTaskQueue->start();
}

void MainWindow::addToQueue()
{
    if (ui->treeWidget->selectedItems().empty())
        return;

    foreach (QTreeWidgetItem *item, ui->treeWidget->selectedItems()) {
        BackupTask *task = tasks.value(item->text(0));

        if (task->isAbleToPerform()) {
            nTaskQueue->put(task);
        } else {
            QMessageBox::critical(this, tr("Error"), tr("Invalid task"));
        }
    }
}

void MainWindow::shutdownSystem()
{
    TimedMessageBox *messageBox = new TimedMessageBox(
                            60,
                            TimedMessageBox::Question,
                            tr("Shutdown"),
                            tr("Do you want to shutdown now? (%1)"),
                            TimedMessageBox::No | TimedMessageBox::Yes
                        );

    messageBox->setDefaultButton(TimedMessageBox::Yes);

    if (messageBox->exec() == TimedMessageBox::Yes) {
        qDebug() << "Shutdown " << QTime::currentTime();
#ifdef Q_OS_WIN32
        QProcess::startDetached("shutdown -s -f -t 00");
#endif
#ifdef Q_OS_LINUX
        //QProcess::startDetached("shutdown -P now");
#endif
    }
}

void MainWindow::addNewTask()
{
    QString name = enterTaskName();
    if (name.isEmpty())
        return;

    tasks.insert(name, new BackupTask(name));
    addTaskItemToTree(ui->treeWidget, tasks.value(name));
    openTaskSettings(tasks.value(name));
}

void MainWindow::removeTask()
{
    QList<QTreeWidgetItem*> items = ui->treeWidget->selectedItems();

    QSettings *settings = new QSettings(this);

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
    if (task == nullptr) return;

    TaskSettings *taskSettings = new TaskSettings(task);

    connect(taskSettings, SIGNAL(accepted()), this, SLOT(loadAllTasks()));
    taskSettings->show();
}

void MainWindow::loadAllTasks()
{
    ui->treeWidget->clear();

    QSettings *settings = new QSettings(this);

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
    TQForm->show();
}

void MainWindow::on_actionRunBackup_triggered()
{
    on_actionAdd_to_queue_triggered();
    nTaskQueue->start();
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

QString MainWindow::enterTaskName()
{
    bool succes = false;
    QString name = QInputDialog::getText(
                            this, tr("Name"),
                            tr("Enter new backup name:"),
                            QLineEdit::Normal,"",&succes);

    if(succes==false)
        return "";
    else
        return name;
}

void MainWindow::addTaskItemToTree(QTreeWidget *tree, const BackupTask *task)
{
    BackupTaskSpecs *specs = task->specs;

    QStringList taskSettings;
    taskSettings << specs->getName()
                 << specs->getPathFrom()
                 << specs->getPathTo()
                 << specs->getSchedule()->toString();

    QTreeWidgetItem *item = new QTreeWidgetItem(tree, taskSettings);
    tree->addTopLevelItem(item);
}

void MainWindow::scheduleBackup(const BackupTask *task)
{
    if(task->specs->getAutoBackup())
        qDebug() << connect(task, &BackupTask::timeout,
                            this, &MainWindow::onTaskTimeout, Qt::UniqueConnection);
    else
        disconnect(task, &BackupTask::timeout, this, &MainWindow::onTaskTimeout);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    event->ignore();
    this->hide();
}

void MainWindow::initTray()
{
    exitAction = new QAction(tr("Exit"), this);
    showHideAction = new QAction(tr("Show/Hide"), this);

    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
    connect(showHideAction, &QAction::triggered, this, [=] () {
        this->setVisible(!this->isVisible());
    } );

    QMenu *trayMenu = new QMenu("QBackup", this);
    trayMenu->addAction(showHideAction);
    trayMenu->addAction(exitAction);

    QPixmap pixmap(":/images/icon.png");
    QIcon icon(pixmap.scaled(128, 128));
    tray->setIcon(icon);
    tray->setContextMenu(trayMenu);
    tray->setVisible(true);
}

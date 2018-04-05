#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadTasksWidget();

    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
            this, 			SLOT(openTaskSettings(QTreeWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAddTask_triggered()
{
    addNewTask();
}

void MainWindow::loadTask(QString name)
{
    QStringList taskSettings;
    BackupTask *task = new BackupTask(name);
    taskSettings << task->specs->getName() << task->specs->getPathFrom() << task->specs->getPathTo();

    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget, taskSettings);
    ui->treeWidget->addTopLevelItem(item);
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

    BackupTask task(name);
}

void MainWindow::removeTask()
{
    QList<QTreeWidgetItem*> items = ui->treeWidget->selectedItems();

    QSettings *settings = new QSettings(this);

    foreach(QTreeWidgetItem *item, items){
        settings->remove(item->text(0));
    }

    settings->deleteLater();

    loadTasksWidget();
}

void MainWindow::openTaskSettings(QTreeWidgetItem *item)
{
    QString name = item->text(0);
    TaskSettings *taskSettings = new TaskSettings(name);

    connect(taskSettings, SIGNAL(finished(int)), taskSettings, SLOT(deleteLater()));
    taskSettings->show();

}

void MainWindow::loadTasksWidget()
{
    ui->treeWidget->clear();

    QSettings *settings = new QSettings(this);
    settings->beginGroup("Tasks");

    QStringList taskNames = settings->childGroups();
    settings->deleteLater();

    foreach(QString taskName, taskNames) {
        loadTask(taskName);
    }
}

void MainWindow::on_actionRemoveTask_triggered()
{
    removeTask();
}

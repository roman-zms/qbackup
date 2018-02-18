#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QInputDialog>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadTasksWidget();
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
    taskSettings << task->getName() << task->getPathFrom() << task->getPathTo();

    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget, taskSettings);
    ui->treeWidget->addTopLevelItem(item);
}

void MainWindow::addNewTask()
{
    /*
    QString name;
    bool succes;

    do {
        name = QInputDialog::getText(
                this, tr("Name"),
                tr("Enter new backup name:"),
                QLineEdit::Normal,"",&succes);
    } while(succes && name.isEmpty());

    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget, name.append(",/path/from/,/path/to/").split(','));
    item->setCheckState(0, Qt::CheckState::Unchecked);
    ui->treeWidget->addTopLevelItem(item);
    */
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

void MainWindow::loadTasksWidget()
{
    ui->treeWidget->clear();

    QSettings *setttings = new QSettings(this);
    QStringList taskNames = setttings->childGroups();
    setttings->deleteLater();

    foreach(QString taskName, taskNames) {
        loadTask(taskName);
    }
}

void MainWindow::on_actionRemoveTask_triggered()
{
    removeTask();
}

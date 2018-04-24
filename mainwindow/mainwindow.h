#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QInputDialog>
#include <QSettings>

#include "backuptask/backuptask.h"
#include "tasksettings/tasksettings.h"
#include "queue/taskqueue.h"
#include "generalsettings/generalsettings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAddTask_triggered();
    void on_actionRemoveTask_triggered();

    void addNewTask();
    void removeTask();

    void openTaskSettings(QTreeWidgetItem*);
    void openTaskSettings(BackupTask *task);

    void loadAllTasks();
    void loadTask(QString name);

    void onTaskTimeout();

    void on_actionShow_queue_triggered();

    void on_actionRunBackup_triggered();

    void on_actionSettings_triggered();

    void on_actionAdd_to_queue_triggered();

private:
    Ui::MainWindow *ui;
    TaskQueue *taskQueue;

    QMap<QString, BackupTask*> tasks;

    GeneralSettings *gSettings;
};

#endif // MAINWINDOW_H

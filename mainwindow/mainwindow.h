#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QInputDialog>
#include <QSettings>
#include <QMessageBox>
#include <QSystemTrayIcon>

#include <queue/ntaskqueue.h>
#include <queue/taskqueueform.h>

#include "backuptask/backuptask.h"
#include "tasksettings/tasksettings.h"
#include "queue/taskqueue.h"
#include "generalsettings/generalsettings.h"
#include "backuptask/taskschedule.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
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

    void addToQueue();

    void shutdownSystem();

    void on_actionShow_queue_triggered();
    void on_actionRunBackup_triggered();
    void on_actionSettings_triggered();
    void on_actionAdd_to_queue_triggered();

protected:
    virtual void closeEvent(QCloseEvent *event) override;

private:
    //QString getScheduleString(const TaskSchedule &schedule);
    QString enterTaskName();
    void addTaskItemToTree(QTreeWidget *tree, const BackupTask *task);
    void scheduleBackup(const BackupTask *task);
    void initTray();


private:
    Ui::MainWindow *ui;

    NTaskQueue *nTaskQueue;
    TaskQueueForm *TQForm;

    QMap<QString, BackupTask*> tasks;

    GeneralSettings *gSettings;

    QSystemTrayIcon *tray;

    QAction *exitAction;
    QAction *showHideAction;

};

#endif // MAINWINDOW_H

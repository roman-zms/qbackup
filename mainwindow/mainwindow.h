#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "backuptask/backuptask.h"

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

    void loadTasksWidget();
    void loadTask(QString name);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

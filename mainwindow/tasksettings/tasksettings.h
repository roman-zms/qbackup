#ifndef TASKSETTINGS_H
#define TASKSETTINGS_H

#include <QDialog>
#include <QModelIndex>
#include <QTreeWidgetItem>

#include "backuptask/backuptask.h"

namespace Ui {
class TaskSettings;
}

class TaskSettings : public QDialog
{
    Q_OBJECT

public:
    explicit TaskSettings(BackupTask *task, QWidget *parent = 0);
    ~TaskSettings();

private slots:
    void init();
    void save();

    void on_fromPushButton_clicked();

    void on_toPushButton_clicked();

    void treeWidgetItemChanged(QTreeWidgetItem*, int);
    void treeWidgetItemClicked(QModelIndex index);

    void on_buttonBox_accepted();

private:
    Ui::TaskSettings *ui;
    BackupTask *task;
    QList<bool> _days;

};

#endif // TASKSETTINGS_H

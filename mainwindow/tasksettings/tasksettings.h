#ifndef TASKSETTINGS_H
#define TASKSETTINGS_H

#include <QDialog>
#include <QModelIndex>

namespace Ui {
class TaskSettings;
}

class TaskSettings : public QDialog
{
    Q_OBJECT

public:
    explicit TaskSettings(QString name, QWidget *parent = 0);
    ~TaskSettings();

private slots:
    void on_fromPushButton_clicked();

    void on_toPushButton_clicked();


private:
    Ui::TaskSettings *ui;

};

#endif // TASKSETTINGS_H

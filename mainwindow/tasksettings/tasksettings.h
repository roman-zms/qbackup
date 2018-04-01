#ifndef TASKSETTINGS_H
#define TASKSETTINGS_H

#include <QDialog>

namespace Ui {
class TaskSettings;
}

class TaskSettings : public QDialog
{
    Q_OBJECT

public:
    explicit TaskSettings(QString name, QWidget *parent = 0);
    ~TaskSettings();

private:
    Ui::TaskSettings *ui;
};

#endif // TASKSETTINGS_H

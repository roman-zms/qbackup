#include "tasksettings.h"
#include "ui_tasksettings.h"

TaskSettings::TaskSettings(QString name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskSettings)
{
    ui->setupUi(this);
}

TaskSettings::~TaskSettings()
{
    delete ui;
}

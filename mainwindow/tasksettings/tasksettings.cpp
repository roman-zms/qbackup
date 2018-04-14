#include "tasksettings.h"
#include "ui_tasksettings.h"
#include "qfiledialog.h"

#include <QDebug>

TaskSettings::TaskSettings(QString name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskSettings)
{
    ui->setupUi(this);

    connect(ui->checkBox, SIGNAL(toggled(bool)), ui->treeWidget, SLOT(setEnabled(bool)));
    connect(ui->checkBox, SIGNAL(toggled(bool)), ui->timeEdit, SLOT(setEnabled(bool)));

}

TaskSettings::~TaskSettings()
{
    delete ui;
}

void TaskSettings::on_fromPushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Directory Dialog", QDir::homePath());
    ui->lineEditFrom->setText(dir);
}

void TaskSettings::on_toPushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Directory Dialog", QDir::homePath());
    ui->lineEditTo->setText(dir);
}



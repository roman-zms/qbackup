#include "tasksettings.h"
#include "ui_tasksettings.h"
#include "qfiledialog.h"

#include <QDebug>

TaskSettings::TaskSettings(BackupTask *task, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskSettings),
    task(task)
{
    ui->setupUi(this);

    connect(ui->autoBackupCheckBox, SIGNAL(toggled(bool)), ui->treeWidget, SLOT(setEnabled(bool)));
    connect(ui->autoBackupCheckBox, SIGNAL(toggled(bool)), ui->timeEdit, SLOT(setEnabled(bool)));

    connect(ui->treeWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(treeWidgetItemClicked(QModelIndex)));

    connect(this, &TaskSettings::finished, this, &TaskSettings::deleteLater);

    this->setWindowTitle(task->specs->getName());
    init();
}

void TaskSettings::accept()
{
    save();
    this->close();
    emit accepted();
}

TaskSettings::~TaskSettings()
{
    delete ui;
}

void TaskSettings::init()
{
    for (int i = 0; i < 7; i++) _days.append(false);

    ui->lineEditFrom->setText(task->specs->getPathFrom());
    ui->lineEditTo->setText(task->specs->getPathTo());

    ui->uploadCheckBox->setChecked(task->specs->getUpload());
    ui->autoBackupCheckBox->setChecked(task->specs->getAutoBackup());
    ui->shutdownCheckBox->setChecked(task->specs->getShutdown());

    for ( int i = 0; i < 7; i++) {
        Qt::CheckState state;
        if(task->specs->getSchedule()->getDay(i) == true)
            state = Qt::Checked;
        else
            state = Qt::Unchecked;
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        QString name = item->text(0);
        item->setCheckState(0, state);
        _days.replace(i, state);
        //ui->treeWidget->itemAt(i, 0)->setCheckState(0, state);
    }
    ui->timeEdit->setTime(task->specs->getSchedule()->getTime());
}

void TaskSettings::save()
{
    task->specs->setPathFrom(ui->lineEditFrom->text());
    task->specs->setPathTo(ui->lineEditTo->text());

    task->specs->setUpload(ui->uploadCheckBox->isChecked());
    task->specs->setAutoBackup(ui->autoBackupCheckBox->isChecked());
    task->specs->setShutdown(ui->shutdownCheckBox->isChecked());

    //for(int i=0; i<7; i++)
    //    task->specs->getSchedule()->setDay(i, _days.at(i));

    for (int i = 0; i < 7; i++) {
        task->specs->getSchedule()->setDay(i, _days.at(i));
    }

    task->specs->getSchedule()->setTime(ui->timeEdit->time());
    task->sync();
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

void TaskSettings::treeWidgetItemClicked(QModelIndex index)
{
    int row = index.row();
    bool checked = ui->treeWidget->topLevelItem(row)->checkState(0);
    _days.replace(row, checked);
}


void TaskSettings::on_buttonBox_accepted()
{
    //save();
    //this->accept();
    //this->deleteLater();
}

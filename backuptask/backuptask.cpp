#include "backuptask.h"

BackupTask::BackupTask(QString name, QObject *parent) : QObject(parent)
{
    settings = new QSettings(this);
    settings->beginGroup("Tasks");
    settings->beginGroup(name);

    specs = new BackupTaskSpecs(name);
    initTask();
}

BackupTask::~BackupTask()
{
    saveTask();
    settings->sync();
    settings->deleteLater();
}


void BackupTask::initTask()
{
    this->specs->setPathFrom(settings->value("PathFrom").toString());
    this->specs->setPathTo(settings->value("PathTo").toString());

    this->specs->setAutoBackup(settings->value("AutoBackup").toBool());
    this->specs->setUpload(settings->value("Upload").toBool());

    QList<QVariant> days = settings->value("Days").toList();
    for(int i=0; i<7; i++)
    if(!days.isEmpty()){
        this->specs->getSchedule()->setDay(i, days.at(i).toBool());
    } else {
        this->specs->getSchedule()->setDay(i, false);
    }

    this->specs->getSchedule()->setTime(settings->value("Time").toTime());
}

void BackupTask::saveTask()
{
    settings->setValue("PathFrom",    this->specs->getPathFrom());
    settings->setValue("PathTo",      this->specs->getPathTo());
    settings->setValue("AutoBackup",  this->specs->getAutoBackup());
    settings->setValue("Upload",      this->specs->getUpload());
    settings->setValue("Days",		  this->specs->getSchedule()->getDays());
    settings->setValue("Time",		  this->specs->getSchedule()->getTime());
}

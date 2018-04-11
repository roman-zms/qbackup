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
    if(settings->contains(specs->getName())) {
        this->specs->setPathFrom(settings->value("PathFrom").toString());
        this->specs->setPathTo(settings->value("PathTo").toString());

        this->specs->setAutoBackup(settings->value("AutoBackup").toBool());
        this->specs->setUpload(settings->value("Upload").toBool());
    } else {
        saveTask();
    }
}

void BackupTask::saveTask()
{
    settings->setValue("PathFrom",    this->specs->getPathFrom());
    settings->setValue("PathTo",      this->specs->getPathTo());
    settings->setValue("AutoBackup",  this->specs->getAutoBackup());
    settings->setValue("Upload",      this->specs->getUpload());
}

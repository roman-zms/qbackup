#include "backuptask.h"

BackupTask::BackupTask(QString name, QObject *parent) : QObject(parent), name(name)
{
    settings = new QSettings(this);
    initTask();
}

BackupTask::~BackupTask()
{
    saveTask();
    settings->deleteLater();
}

void BackupTask::setPathFrom(const QString &value)
{
    pathFrom = value;
}

void BackupTask::setPathTo(const QString &value)
{
    pathTo = value;
}

QString BackupTask::getName() const
{
    return name;
}

void BackupTask::setName(const QString &value)
{
    name = value;
}

bool BackupTask::getAutoBackup() const
{
    return autoBackup;
}

void BackupTask::setAutoBackup(bool value)
{
    autoBackup = value;
}

bool BackupTask::getUpload() const
{
    return upload;
}

void BackupTask::setUpload(bool value)
{
    upload = value;
}

bool BackupTask::initTask()
{
    this->pathFrom = settings->value(QString("%1/PathFrom").arg(name)).toString();
    this->pathTo   = settings->value(QString("%1/PathTo").arg(name)).toString();

    this->autoBackup = settings->value(QString("%1/AutoBackup").arg(name)).toBool();
    this->upload	 = settings->value(QString("%1/Upload").arg(name)).toBool();
}

bool BackupTask::saveTask()
{
    settings->setValue(QString("%1/PathFrom").arg(name), this->pathFrom);
    settings->setValue(QString("%1/PathTo").arg(name),   this->pathTo);

    settings->setValue(QString("%1/AutoBackup").arg(name),  this->autoBackup);
    settings->setValue(QString("%1/Upload").arg(name),		this->upload);
}

QString BackupTask::getPathTo() const
{
    return pathTo;
}

QString BackupTask::getPathFrom() const
{
    return pathFrom;
}

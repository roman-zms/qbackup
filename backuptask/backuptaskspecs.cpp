#include "backuptaskspecs.h"

BackupTaskSpecs::BackupTaskSpecs(QString name, QObject *parent) : QObject(parent), name(name)
{
    schedule = new TaskSchedule(this);
}

QString BackupTaskSpecs::getName() const
{
    return name;
}

QString BackupTaskSpecs::getPathFrom() const
{
    return pathFrom;
}

void BackupTaskSpecs::setPathFrom(const QString &value)
{
    pathFrom = value;
}

QString BackupTaskSpecs::getPathTo() const
{
    return pathTo;
}

void BackupTaskSpecs::setPathTo(const QString &value)
{
    pathTo = value;
}

bool BackupTaskSpecs::getAutoBackup() const
{
    return autoBackup;
}

void BackupTaskSpecs::setAutoBackup(bool value)
{
    autoBackup = value;
}

bool BackupTaskSpecs::getUpload() const
{
    return upload;
}

void BackupTaskSpecs::setUpload(bool value)
{
    upload = value;
}

TaskSchedule *BackupTaskSpecs::getSchedule() const
{
    return schedule;
}

bool BackupTaskSpecs::getShutdown() const
{
    return shutdown;
}

void BackupTaskSpecs::setShutdown(bool value)
{
    shutdown = value;
}

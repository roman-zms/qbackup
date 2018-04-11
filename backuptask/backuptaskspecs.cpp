#include "backuptaskspecs.h"

BackupTaskSpecs::BackupTaskSpecs(QString name, QObject *parent) : QObject(parent), name(name)
{

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

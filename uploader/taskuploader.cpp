#include "taskuploader.h"

TaskUploader::TaskUploader(QString token, QObject *parent) : QObject(parent),
    yd(new YDAPI(this))
{
    yd->setToken(token);
    initConnections();
}

bool TaskUploader::uploadTask(BackupTask *task, QFile *archive)
{
    if (!archive->exists())
        return false;

    yd->uploadToFolder(archive->fileName(), task->specs->getName());
    return true;
}

void TaskUploader::stop()
{
    yd->stop();
}

void TaskUploader::initConnections()
{
    connect(yd, &YDAPI::finished, this, &TaskUploader::finished);
    connect(yd, &YDAPI::onError, this, &TaskUploader::onError);
    connect(yd, &YDAPI::uploadFinished, this, &TaskUploader::uploadFinished);
    connect(yd, &YDAPI::uploadProgress, this, &TaskUploader::uploadProgress);
}

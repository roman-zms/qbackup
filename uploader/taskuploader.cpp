#include "taskuploader.h"

TaskUploader::TaskUploader(QObject *parent) : QObject(parent),
    yd(new YDAPI(this))
{

}

bool TaskUploader::uploadTask(BackupTask *task, QFile *archive)
{
    if (!archive->exists())
        return false;

    yd->uploadToFolder(archive->fileName(), task->specs->getName());
    return true;
}

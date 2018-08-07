#ifndef TASKUPLOADER_H
#define TASKUPLOADER_H

#include "ydapi.h"

#include <QFile>
#include <QObject>

#include <backuptask/backuptask.h>

class TaskUploader : public QObject
{
public:
    explicit TaskUploader(QObject *parent);
    bool uploadTask(BackupTask *task, QFile *archive);

private:
    YDAPI *yd;
};

#endif // TASKUPLOADER_H

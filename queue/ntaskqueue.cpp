#include "ntaskqueue.h"
#include <queue/state/ntaskstate.h>
#include <queue/state/ncompressingtaskstate.h>
#include <queue/state/nuploadingtaskstate.h>
#include <queue/state/nwaitingtaskstate.h>

#include <QList>

NTaskQueue::NTaskQueue(QObject *parent) : QObject(parent),
    compressing(new NCompressingTaskState(this)),
    uploading(new NUploadingTaskState(this)),
    waiting(new NWaitingTaskState(this)),
    state(waiting),
    yd(new YDAPI(this)),
    compressor(new TaskCompressor(this))
{
    connect(compressor, &TaskCompressor::onCompressSucces, this, &NTaskQueue::finished);
    connect(yd, &YDAPI::uploadFinished, this, &NTaskQueue::finished);
}

bool NTaskQueue::put(BackupTask *task)
{
    taskList.append(task);
    return true;
}

bool NTaskQueue::start()
{
    return state->start();
}

bool NTaskQueue::stop()
{
    return state->stop();
}

bool NTaskQueue::clear()
{
    return state->clear();
}

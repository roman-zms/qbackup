#include <queue/ntaskqueue.h>
#include <queue/state/ntaskstate.h>
#include <queue/state/ncompressingtaskstate.h>
#include <queue/state/nuploadingtaskstate.h>
#include <queue/state/nwaitingtaskstate.h>
#include <queue/state/nstatefactory.h>

#include <QList>
#include <QDebug>

NTaskQueue::NTaskQueue(QObject *parent) : QObject(parent),
    factory(new NStateFactory(this)),
    state(factory->waiting()),
    uploader(new TaskUploader(QSettings().value("Token").toString(), this)),
    compressor(new TaskCompressor(this)),
    currentTask(nullptr)
{
    connect(compressor, &TaskCompressor::onCompressSucces, this, &NTaskQueue::finish);
    connect(uploader, &TaskUploader::uploadFinished, this, &NTaskQueue::finish);

    connect(compressor, &TaskCompressor::compressProgress, this, &NTaskQueue::onProgress);
    connect(uploader, &TaskUploader::uploadProgress, this, &NTaskQueue::onProgress);
}

bool NTaskQueue::put(BackupTask *task)
{
    taskList.append(task);
    emit added();
    return true;
}

bool NTaskQueue::start()
{
    bool succes = state->start();
    if (succes) {
        emit started();
        qDebug() << "Started";
    }

    return succes;
}

bool NTaskQueue::stop()
{
    bool succes = state->stop();
    if (succes) {
        emit stopped();
        qDebug() << "Stoped";
    }

    return succes;
}

bool NTaskQueue::clear()
{
    bool succes = state->clear();
    if (succes) {
        emit cleared();
        qDebug() << "Cleared";
    }

    return succes;
}

int NTaskQueue::getSize() const
{
    return taskList.size();
}

int NTaskQueue::getCurrentProgress()
{
    if (total > 0) {
        qint64 progress = ((100*done)/total);
        return static_cast<int>(progress);
    } else {
        return 0;
    }
}

void NTaskQueue::finish()
{
    bool succes = state->finished();
    if (succes) {
        emit finished();
        qDebug() << "Finished";
    }
}

void NTaskQueue::onProgress(qint64 done, qint64 total)
{
    emit progress(done, total);
    this->done = done;
    this->total = total;
}

void NTaskQueue::setState(NTaskState *state)
{
    this->state = state;
    qDebug() << "The NTaskQueue state is: " << state->stateName();
}

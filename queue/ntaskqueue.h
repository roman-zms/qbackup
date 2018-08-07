#ifndef NTASKQUEUE_H
#define NTASKQUEUE_H

#include <QObject>

#include <backuptask/backuptask.h>
#include <uploader/ydapi.h>
#include <compressor/taskcompressor.h>

class NTaskState;

class NTaskQueue : public QObject
{
    Q_OBJECT
public:
    explicit NTaskQueue(QObject *parent = nullptr);

    enum StateType {
        Waiting,
        Compressing,
        Compressed,
        Uploading,
        Uploaded
    };

    bool put(BackupTask *task);
    bool start();
    bool stop();
    bool clear();

    friend NTaskState;

public slots:
    void finished();

private:
    void changeState(StateType state);

private:
    NTaskState *compressing;
    NTaskState *uploading;
    NTaskState *waiting;
    NTaskState *state;

    YDAPI *yd;
    TaskCompressor *compressor;

    QList<BackupTask *> taskList;
    BackupTask *currentTask;
};

#endif // NTASKQUEUE_H

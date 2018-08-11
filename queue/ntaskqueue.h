#ifndef NTASKQUEUE_H
#define NTASKQUEUE_H

#include <QObject>

#include <backuptask/backuptask.h>
#include <uploader/taskuploader.h>
#include <uploader/ydapi.h>
#include <compressor/taskcompressor.h>

class NTaskState;
class NStateFactory;
class NTaskQueueModel;

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

    int getSize() const;

    int getCurrentProgress();

    friend NTaskState;
    friend NTaskQueueModel;

public slots:
    void finish();

signals:
    void added();
    void started();
    void stopped();
    void cleared();
    void finished();
    void progress(qint64 done, qint64 total);

private slots:
    void onProgress(qint64 done, qint64 total);

private:
    void setState(NTaskState *state);

private:
    NStateFactory *factory;
    NTaskState *compressing;
    NTaskState *uploading;
    NTaskState *waiting;
    NTaskState *state;

    TaskUploader *uploader;
    TaskCompressor *compressor;

    QList<BackupTask *> taskList;
    BackupTask *currentTask;

    qint64 done = 0;
    qint64 total = 0;
};

#endif // NTASKQUEUE_H

#ifndef NTASKSTATE_H
#define NTASKSTATE_H

#include <QObject>

#include "backuptask/backuptask.h"
#include "queue/ntaskqueue.h"

class NStateFactory;

class NTaskState : public QObject
{
    Q_OBJECT
public:
    explicit NTaskState(NTaskQueue *parent);
    virtual ~NTaskState();

    virtual bool put(BackupTask *task);
    virtual bool start();
    virtual bool stop();
    virtual bool clear();
    virtual bool finished();

    virtual QString stateName() = 0;

protected:
    QList<BackupTask*>& getTaskList();
    TaskCompressor* getCompressor();
    TaskUploader* getUploader();
    void setState(NTaskState *state);
    bool setCurrentTask(BackupTask *task);
    BackupTask* getCurrentTask();

    void turnOnShutdown();
    void turnOffShutdown();
    bool isShutdown();

protected:
    NTaskQueue *queue;
    NStateFactory *factory;

public slots:
};

#endif // NTASKSTATE_H

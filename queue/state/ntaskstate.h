#ifndef NTASKSTATE_H
#define NTASKSTATE_H

#include <QObject>

#include "backuptask/backuptask.h"
#include "queue/ntaskqueue.h"

class NTaskState : public QObject
{
    Q_OBJECT
public:
    explicit NTaskState(NTaskQueue *parent);
    virtual ~NTaskState();

    //virtual bool put(BackupTask *task);
    virtual bool start();
    virtual bool stop();
    virtual bool clear();
    virtual bool finished();

protected:
    QList<BackupTask*>& getTaskList();
    TaskCompressor* getCompressor();
    YDAPI* getYD();
    void changeState(NTaskQueue::StateType state);
    bool setCurrentTask(BackupTask *task);
    BackupTask* getCurrentTask();

protected:
    NTaskQueue *queue;

public slots:
};

#endif // NTASKSTATE_H

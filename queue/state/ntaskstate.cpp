#include "ntaskstate.h"

NTaskState::NTaskState(NTaskQueue *parent) : QObject(parent), queue(parent)
{

}

NTaskState::~NTaskState()
{

}

bool NTaskState::start()
{
    return false;
}

bool NTaskState::stop()
{
    return false;
}

bool NTaskState::clear()
{
    return false;
}

bool NTaskState::finished()
{
    return false;
}

bool NTaskState::put(BackupTask *task)
{
    getTaskList().append(task);
    return true;
}

QList<BackupTask *> &NTaskState::getTaskList()
{
    return queue->taskList;
}

TaskCompressor *NTaskState::getCompressor()
{
    return queue->compressor;
}

YDAPI *NTaskState::getYD()
{
    return queue->yd;
}

void NTaskState::changeState(NTaskQueue::StateType state)
{
    queue->changeState(state);
}

bool NTaskState::setCurrentTask(BackupTask *task)
{
    queue->currentTask = task;

    return queue->currentTask != nullptr;
}

BackupTask *NTaskState::getCurrentTask()
{
    return queue->currentTask;
}

#include "nwaitingtaskstate.h"

bool NWaitingTaskState::start()
{
    if (getTaskList().isEmpty())
        return false;

    setCurrentTask(getTaskList().takeFirst());

    if (getCompressor()->compressTask(getCurrentTask())) {
        changeState(NTaskQueue::StateType::Compressing);
        return true;
    } else {
        return false;
    }
}

bool NWaitingTaskState::clear()
{
    getTaskList().clear();
    return true;
}

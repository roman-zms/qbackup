#include "nwaitingtaskstate.h"
#include <queue/state/nstatefactory.h>

bool NWaitingTaskState::start()
{
    if (getTaskList().isEmpty())
        return false;

    setCurrentTask(getTaskList().first());

    if (getCompressor()->compressTask(getCurrentTask())) {
        setState(factory->compressing());
        return true;
    } else {
        return false;
    }
}

bool NWaitingTaskState::clear()
{
    getTaskList().clear();
    setCurrentTask(nullptr);
    return true;
}


QString NWaitingTaskState::stateName()
{
    return "Waiting";
}

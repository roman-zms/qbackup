#include "nuploadedstate.h"

bool NUploadedState::start()
{
    changeState(NTaskQueue::Waiting);

    if (!getTaskList().isEmpty())
        return queue->start();

    return true;
}

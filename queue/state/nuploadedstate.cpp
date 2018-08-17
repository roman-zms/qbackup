#include "nuploadedstate.h"
#include <queue/state/nstatefactory.h>

bool NUploadedState::start()
{
    setCurrentTask(nullptr);
    getTaskList().removeFirst();
    setState(factory->waiting());

    return queue->start();
}


QString NUploadedState::stateName()
{
    return "Uploaded";
}

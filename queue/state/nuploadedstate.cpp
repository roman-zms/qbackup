#include "nuploadedstate.h"
#include <queue/state/nstatefactory.h>

bool NUploadedState::start()
{
    setState(factory->waiting());

    if (!getTaskList().isEmpty())
        return queue->start();

    return true;
}


QString NUploadedState::stateName()
{
    return "Uploaded";
}

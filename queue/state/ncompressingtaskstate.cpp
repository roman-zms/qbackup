#include "ncompressingtaskstate.h"
#include <queue/state/nstatefactory.h>

bool NCompressingTaskState::stop()
{
    getCompressor()->stop();
    setCurrentTask(nullptr);
    turnOffShutdown();

    setState(factory->waiting());
    return true;
}

bool NCompressingTaskState::finished()
{
    setState(factory->compressed());
    return !queue->start();
}


QString NCompressingTaskState::stateName()
{
    return "Compressing";
}

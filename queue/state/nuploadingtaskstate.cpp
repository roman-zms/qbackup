#include "nuploadingtaskstate.h"
#include <queue/state/nstatefactory.h>

bool NUploadingTaskState::stop()
{
    getUploader()->stop();
    setCurrentTask(nullptr);
    turnOffShutdown();

    setState(factory->waiting());
    return true;
}


bool NUploadingTaskState::finished()
{
    setState(factory->uploaded());

    return !queue->start();
}


QString NUploadingTaskState::stateName()
{
    return "Uploading";
}

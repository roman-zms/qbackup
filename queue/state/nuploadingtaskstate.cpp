#include "nuploadingtaskstate.h"
#include <queue/state/nstatefactory.h>

bool NUploadingTaskState::stop()
{
    getUploader()->stop();

    setCurrentTask(nullptr);

    setState(factory->waiting());
    return true;
}


bool NUploadingTaskState::finished()
{
    setState(factory->uploaded());
    setCurrentTask(nullptr);
    getTaskList().removeFirst();

    return !queue->start();
}


QString NUploadingTaskState::stateName()
{
    return "Uploading";
}

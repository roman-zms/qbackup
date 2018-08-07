#include "nuploadingtaskstate.h"

bool NUploadingTaskState::stop()
{
    getYD()->stop();

    getTaskList().push_front(getCurrentTask());
    setCurrentTask(nullptr);

    changeState(NTaskQueue::StateType::Waiting);
    return true;
}


bool NUploadingTaskState::finished()
{
    changeState(NTaskQueue::Uploaded);
    return queue->start();
}

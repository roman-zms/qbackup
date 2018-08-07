#include "ncompressingtaskstate.h"

bool NCompressingTaskState::stop()
{
    getCompressor()->stop();

    getTaskList().push_front(getCurrentTask());
    setCurrentTask(nullptr);

    changeState(NTaskQueue::StateType::Waiting);
    return true;
}

bool NCompressingTaskState::finished()
{
    changeState(NTaskQueue::Compressed);
    return queue->start();
}

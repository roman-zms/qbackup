#include "ncompressedstate.h"

bool NCompressedState::start()
{
    if (getCurrentTask()->specs->getUpload()) {
        //getYD()->
        changeState(NTaskQueue::Uploading);
        return true;
    } else {
        changeState(NTaskQueue::Waiting);
        return queue->start();
    }
}

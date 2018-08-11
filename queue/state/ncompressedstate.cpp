#include "ncompressedstate.h"
#include <queue/state/nstatefactory.h>

bool NCompressedState::start()
{
    if (getCurrentTask()->specs->getUpload()) {
        getUploader()->uploadTask(getCurrentTask(), getCompressor()->getLastAcrhive());
        setState(factory->uploading());

        return true;
    } else {
        setCurrentTask(nullptr);
        getTaskList().removeFirst();
        setState(factory->waiting());

        return queue->start();
    }
}


QString NCompressedState::stateName()
{
    return "Compressed";
}

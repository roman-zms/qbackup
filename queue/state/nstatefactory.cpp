#include "nstatefactory.h"

#include "ncompressedstate.h"
#include "ncompressingtaskstate.h"
#include "nuploadedstate.h"
#include "nuploadingtaskstate.h"
#include "nwaitingtaskstate.h"


NStateFactory::NStateFactory(NTaskQueue *parent) : QObject(parent), parent(parent)  {}

NTaskState *NStateFactory::waiting()
{
    if (m_waiting == nullptr) {
        m_waiting = new NWaitingTaskState(parent);
    }

    return m_waiting;
}

NTaskState *NStateFactory::compressing()
{
    if (m_compressing == nullptr) {
        m_compressing = new NCompressingTaskState(parent);
    }

    return m_compressing;
}

NTaskState *NStateFactory::compressed()
{
    if (m_compressed == nullptr) {
        m_compressed = new NCompressedState(parent);
    }

    return m_compressed;
}

NTaskState *NStateFactory::uploading()
{
    if (m_uploading == nullptr) {
        m_uploading = new NUploadingTaskState(parent);
    }

    return m_uploading;
}

NTaskState *NStateFactory::uploaded()
{
    if (m_uploaded == nullptr) {
        m_uploaded = new NUploadedState(parent);
    }

    return m_uploaded;
}

#ifndef NUPLOADINGTASKSTATE_H
#define NUPLOADINGTASKSTATE_H

#include <queue/state/ntaskstate.h>
#include <queue/ntaskqueue.h>

class NUploadingTaskState : public NTaskState
{
public:
    using NTaskState::NTaskState;

    // NTaskState interface
    virtual bool stop() override;
    virtual bool finished() override;

    // NTaskState interface
public:
    virtual QString stateName() override;
};

#endif // NUPLOADINGTASKSTATE_H

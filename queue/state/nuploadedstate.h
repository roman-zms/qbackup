#ifndef NUPLOADEDSTATE_H
#define NUPLOADEDSTATE_H

#include <queue/state/ntaskstate.h>
#include <queue/ntaskqueue.h>

class NUploadedState : public NTaskState
{
    // NTaskState interface
public:
    using NTaskState::NTaskState;
    virtual bool start() override;
};

#endif // NUPLOADEDSTATE_H

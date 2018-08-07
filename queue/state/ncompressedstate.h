#ifndef NCOMPRESSEDSTATE_H
#define NCOMPRESSEDSTATE_H

#include <queue/state/ntaskstate.h>

class NCompressedState : public NTaskState
{
    // NTaskState interface
public:
    using NTaskState::NTaskState;
    virtual bool start() override;
};

#endif // NCOMPRESSEDSTATE_H

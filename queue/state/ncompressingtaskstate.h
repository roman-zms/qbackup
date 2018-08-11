#ifndef NRUNNUNGTASKSTATE_H
#define NRUNNUNGTASKSTATE_H

#include "ntaskstate.h"
#include <queue/ntaskqueue.h>

class NCompressingTaskState : public NTaskState
{
public:
    using NTaskState::NTaskState;

    // NTaskState interface
public:
    virtual bool stop() override;
    virtual bool finished() override;

    // NTaskState interface
public:
    virtual QString stateName() override;
};

#endif // NRUNNUNGTASKSTATE_H

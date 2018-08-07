#ifndef NWAITINGTASKSTATE_H
#define NWAITINGTASKSTATE_H

#include <queue/state/ntaskstate.h>
#include <queue/ntaskqueue.h>

class NWaitingTaskState : public NTaskState
{
public:
    using NTaskState::NTaskState;

    virtual bool start() override;
    virtual bool clear() override;

};

#endif // NWAITINGTASKSTATE_H

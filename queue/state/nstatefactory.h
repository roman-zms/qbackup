#ifndef NSTATEFACTORY_H
#define NSTATEFACTORY_H

#include <queue/state/ntaskstate.h>
#include <queue/ntaskqueue.h>

#include <QObject>

class NStateFactory : public QObject
{
    Q_OBJECT
public:
    explicit NStateFactory(NTaskQueue *parent);

    NTaskState *waiting();
    NTaskState *compressing();
    NTaskState *compressed();
    NTaskState *uploading();
    NTaskState *uploaded();

private:
    NTaskQueue *parent;

    NTaskState *m_waiting = nullptr;
    NTaskState *m_compressing = nullptr;
    NTaskState *m_compressed = nullptr;
    NTaskState *m_uploading = nullptr;
    NTaskState *m_uploaded = nullptr;
};

#endif // NSTATEFACTORY_H

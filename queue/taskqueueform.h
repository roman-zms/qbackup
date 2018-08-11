#ifndef TASKQUEUEFORM_H
#define TASKQUEUEFORM_H

#include "ntaskqueue.h"

#include <QWidget>

namespace Ui {
class TaskQueueForm;
}

class TaskQueueForm : public QWidget
{
    Q_OBJECT

public:
    explicit TaskQueueForm(NTaskQueue *queue, QWidget *parent = nullptr);
    ~TaskQueueForm();

private:
    void initConnections();

private:
    Ui::TaskQueueForm *ui;
    NTaskQueue *queue;
};

#endif // TASKQUEUEFORM_H

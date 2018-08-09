#include "taskqueueform.h"
#include "ui_taskqueueform.h"

#include <QTreeView>
#include <queue/ntaskqueuemodel.h>

TaskQueueForm::TaskQueueForm(NTaskQueue *queue, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskQueueForm),
    queue(queue)
{
    ui->setupUi(this);
    ui->treeView->setModel(new NTaskQueueModel(queue, this));
}

TaskQueueForm::~TaskQueueForm()
{
    delete ui;
}

void TaskQueueForm::initConnections()
{
    connect(ui->startButton, &QPushButton::clicked, queue, &NTaskQueue::start);
    connect(ui->stopButton, &QPushButton::clicked, queue, &NTaskQueue::stop);
    connect(ui->clearButton, &QPushButton::clicked, queue, &NTaskQueue::clear);
}

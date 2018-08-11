#include "ntaskqueuemodel.h"

#include <queue/state/ncompressingtaskstate.h>

NTaskQueueModel::NTaskQueueModel(NTaskQueue *queue, QObject *parent)
    : QAbstractTableModel(parent),
      queue(queue)
{
    connect(queue, &NTaskQueue::progress, this, &NTaskQueueModel::progressChanged);
    connect(queue, &NTaskQueue::added, this, &NTaskQueueModel::reset);
    connect(queue, &NTaskQueue::cleared, this, &NTaskQueueModel::reset);
    connect(queue, &NTaskQueue::finished, this, &NTaskQueueModel::reset);
    connect(queue, &NTaskQueue::started, this, &NTaskQueueModel::reset);
};

QVariant NTaskQueueModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Vertical)
        return QString::number(section + 1);

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return "Name";
        case 1:
            return "Compressing";
        case 2:
            return "Uploading";
        }
    }

    return QVariant();

}

int NTaskQueueModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME:    int count = queue->getSize();
    return queue->getSize();
}

int NTaskQueueModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return 3;
}

QVariant NTaskQueueModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() > rowCount() || index.column() > rowCount())
        return QVariant();

    if (role == Qt::DisplayRole) {
        if (index.row() == 0 && queue->currentTask != nullptr) {
            switch (index.column()) {
            case 0:
                return queue->currentTask->specs->getName();
            case 1:
                if (queue->state->stateName() == "Compressing") {
                    return queue->getCurrentProgress();
                } else {
                    return 100;
                }
            case 2:
                if (queue->state->stateName() == "Uploading") {
                    return queue->getCurrentProgress();
                } else {
                    //return 0;
                    return QVariant();
                }
            }
        } else {
            int row = index.row();
            switch (index.column()) {
            case 0:
                return queue->taskList.at(row)->specs->getName();
            case 1:
            //return 0;
                return QVariant();
            case 2:
                //return 0;
                return QVariant();
            }
        }
    }

    // FIXME: Implement me!
    return QVariant();

}

void NTaskQueueModel::progressChanged()
{
    if (queue->state->stateName() == "Compressing") {
        emit dataChanged(createIndex(0, 1), createIndex(0, 1));
    } else {
        emit dataChanged(createIndex(0, 2), createIndex(0, 2));
    }
}

void NTaskQueueModel::reset()
{
    endResetModel();
}

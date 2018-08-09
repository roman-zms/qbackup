#include "ntaskqueuemodel.h"

#include <queue/state/ncompressingtaskstate.h>

NTaskQueueModel::NTaskQueueModel(NTaskQueue *queue, QObject *parent)
    : QAbstractItemModel(parent), queue(queue)
{
}

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

QModelIndex NTaskQueueModel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
    if (row > rowCount() || column > columnCount())
        return QModelIndex();

    //return createIndex(row, column, (quintptr)(1000*row + column));
    return createIndex(row, column);
}

QModelIndex NTaskQueueModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
    return QModelIndex();
}

int NTaskQueueModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
    int count = queue->getSize();

    if (queue->currentTask != nullptr)
        count++;

    return count;
}

int NTaskQueueModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
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
                if (queue->state->inherits("NCompressingTaskState")) {
                    return queue->getCurrentProgress();
                } else {
                    return 100;
                }
            case 2:
                if (queue->state->inherits("NUploadingTaskState")) {
                    return queue->getCurrentProgress();
                } else {
                    return 0;
                }
            }
        } else {
            switch (index.column()) {
            case 0:
                return queue->taskList.at(index.row())->specs->getName();
            case 1: case 2:
                return 0;
            }
        }
    }

    // FIXME: Implement me!
    return QVariant();
}

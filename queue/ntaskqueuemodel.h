#ifndef NTASKQUEUEMODEL_H
#define NTASKQUEUEMODEL_H

#include "ntaskqueue.h"

#include <QAbstractItemModel>

class NTaskQueueModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit NTaskQueueModel(NTaskQueue *queue, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    NTaskQueue *queue;
};

#endif // NTASKQUEUEMODEL_H

#ifndef NTASKQUEUEMODEL_H
#define NTASKQUEUEMODEL_H

#include "ntaskqueue.h"

#include <QAbstractTableModel>

class NTaskQueueModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit NTaskQueueModel(NTaskQueue *queue, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private slots:
    void progressChanged();
    void reset();

private:
    NTaskQueue *queue;
};

#endif // NTASKQUEUEMODEL_H

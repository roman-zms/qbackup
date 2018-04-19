#ifndef PROGRESSBARDELEGATE_H
#define PROGRESSBARDELEGATE_H

#include <QStyledItemDelegate>
#include <QApplication>

class ProgressBarDelegate : public QStyledItemDelegate
{
public:
    ProgressBarDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // PROGRESSBARDELEGATE_H

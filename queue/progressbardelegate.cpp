#include "progressbardelegate.h"

ProgressBarDelegate::ProgressBarDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void ProgressBarDelegate::paint(
        QPainter *painter,
        const QStyleOptionViewItem &option,
        const QModelIndex &index
        ) const
{
    QStyleOptionProgressBar progressBarOption;

    if(index.data().toString() != "--") {
        int progress = index.data().toInt();

        QRect r = option.rect;
        progressBarOption.rect = r;

        progressBarOption.textAlignment = Qt::AlignCenter;
        progressBarOption.minimum = 0;
        progressBarOption.maximum = 100;
        progressBarOption.progress = progress;
        progressBarOption.text = QString::number(progress).append("%");
        progressBarOption.textVisible = true;
    }

    QStyledItemDelegate::paint(painter, option, QModelIndex());
    QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);

}

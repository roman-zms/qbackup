#include "taskschedule.h"

#include <QTextStream>

TaskSchedule::TaskSchedule(QObject *parent) : QObject(parent)
{
    for(int i=0; i<7; i++)
        days.append(QVariant(false));

    time = QTime(0,0);
}

QTime TaskSchedule::getTime() const
{
    return time;
}

void TaskSchedule::setTime(const QTime &value)
{
    time = value;
}

bool TaskSchedule::containsDay(int day) const
{
    return days.at(day-1).toBool();
}

QList<QVariant> TaskSchedule::getDays()
{
    return days;
}

bool TaskSchedule::getDay(int day) const
{
    return days.at(day).toBool();
}

void TaskSchedule::setDay(int i, bool value)
{
    days.replace(i, QVariant(value));
}

QString TaskSchedule::toString()
{
    if (getTime().isNull())
        return "";

    QStringList daysOfWeek {
        tr("Mo"),
        tr("Tu"),
        tr("We"),
        tr("Th"),
        tr("Fr"),
        tr("Sa"),
        tr("Su")
    };

    QString string;
    QTextStream str(&string);
    str << getTime().toString("hh:mm") << " ";

    for (int i=0; i<7; i++) {
        if (containsDay(i+1)) {
            str << daysOfWeek.at(i) <<" ";
        }
    }
    return string;
}

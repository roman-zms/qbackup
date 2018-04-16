#ifndef TASKSCHEDULE_H
#define TASKSCHEDULE_H

#include <QObject>
#include <QTime>
#include <QList>
#include <QVariant>

class TaskSchedule : public QObject
{
    Q_OBJECT
public:
    explicit TaskSchedule(QObject *parent = nullptr);
    enum daysOfWeek {
        Monday = 0,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };

    QTime getTime() const;
    void setTime(const QTime &value);

    QList<QVariant> getDays();
    bool getDay(int day) const;
    void setDay(int i, bool value);

private:
    QTime time;
    QList<QVariant> days;
};

#endif // TASKSCHEDULE_H

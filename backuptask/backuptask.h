#ifndef BACKUPTASK_H
#define BACKUPTASK_H

#include <QObject>
#include <QSettings>
#include <QTimer>
#include <QDateTime>

#include "backuptaskspecs.h"

class BackupTask : public QObject
{
    Q_OBJECT
public:
    explicit BackupTask(QString name, QObject *parent = nullptr);
    ~BackupTask();

    bool isAbleToPerform();

    BackupTaskSpecs *specs;

public slots:
    void sync();

private slots:
    void initTimer();

signals:
    void timeout();

private:
    void initTask();
    void saveTask();
    QDateTime getNearestDateTime(const TaskSchedule *schedule);

    //QDateTime nearestDateTime;
    QSettings *settings;
    QTimer *timer;
};

#endif // BACKUPTASK_H

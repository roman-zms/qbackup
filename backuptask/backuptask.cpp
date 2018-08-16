#include "backuptask.h"
#include <QDebug>
#include <QDir>

BackupTask::BackupTask(QString name, QObject *parent) : QObject(parent),
    specs(new BackupTaskSpecs(name)),
    settings(new QSettings(this)),
    timer(new QTimer(this))
{
    settings->beginGroup(name);
    initTask();
}

BackupTask::~BackupTask()
{
    settings->deleteLater();
}

bool BackupTask::isAbleToPerform()
{
    if (QDir(specs->getPathFrom()).isReadable() && QFileInfo(specs->getPathTo()).isWritable()) {
        return true;
    } else {
        return false;
    }
}

void BackupTask::sync()
{
    saveTask();
}

void BackupTask::initTask()
{
    this->specs->setPathFrom(settings->value("PathFrom").toString());
    this->specs->setPathTo(settings->value("PathTo").toString());

    this->specs->setAutoBackup(settings->value("AutoBackup").toBool());
    this->specs->setUpload(settings->value("Upload").toBool());
    this->specs->setShutdown(settings->value("Shutdown").toBool());

    QList<QVariant> days = settings->value("Days").toList();

    for (int i=0; i<7; i++) {
        if (!days.isEmpty()) {
            this->specs->getSchedule()->setDay(i, days.at(i).toBool());
        } else {
            this->specs->getSchedule()->setDay(i, false);
        }
    }

    this->specs->getSchedule()->setTime(settings->value("Time").toTime());

    initTimer();
}

void BackupTask::saveTask()
{
    settings->setValue("PathFrom",    this->specs->getPathFrom());
    settings->setValue("PathTo",      this->specs->getPathTo());
    settings->setValue("AutoBackup",  this->specs->getAutoBackup());
    settings->setValue("Upload",      this->specs->getUpload());
    settings->setValue("Shutdown",	  this->specs->getShutdown());
    settings->setValue("Days",		  this->specs->getSchedule()->getDays());
    settings->setValue("Time",		  this->specs->getSchedule()->getTime());
    settings->sync();
    initTask();
}

QDateTime BackupTask::getNearestDateTime(const TaskSchedule* schedule)
{
    for(int i=0; i<8; i++) {
        QDateTime taskDateTime(QDate::currentDate().addDays(i), schedule->getTime());

        if(schedule->containsDay(taskDateTime.date().dayOfWeek()) &&
                QDateTime::currentDateTime().msecsTo(taskDateTime) > 20000) {
            return taskDateTime;
        }
    }
    return QDateTime();
}

void BackupTask::initTimer()
{
    disconnect(timer, &QTimer::timeout,nullptr,nullptr);
    timer->stop();

    qDebug() << timer->isActive();

    if(!specs->getAutoBackup()) {
        return;
    }

    QDateTime nearest = getNearestDateTime(specs->getSchedule());
    if (!nearest.isValid()) {
        return;
    }

    int msecs = static_cast<int>(QDateTime::currentDateTime().msecsTo(nearest));
    timer->start(msecs);

    qDebug() << msecs;
    qDebug() << "Scheduled at "
             << QDateTime::currentDateTime().addMSecs(msecs);

    connect(timer, &QTimer::timeout, this, &BackupTask::timeout);
    connect(timer, &QTimer::timeout, this, &BackupTask::initTimer);
}

#ifndef BACKUPTASK_H
#define BACKUPTASK_H

#include <QObject>
#include <QSettings>

#include "backuptaskspecs.h"

class BackupTask : public QObject
{
    Q_OBJECT
public:
    explicit BackupTask(QString name, QObject *parent = nullptr);
    ~BackupTask();

    BackupTaskSpecs *specs;

private:
    void initTask();
    void saveTask();

    QSettings *settings;
};

#endif // BACKUPTASK_H

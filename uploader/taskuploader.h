#ifndef TASKUPLOADER_H
#define TASKUPLOADER_H


#include <QFile>
#include <QObject>

#include <backuptask/backuptask.h>
#include <uploader/ydapi.h>

class TaskUploader : public QObject
{
    Q_OBJECT
public:
    explicit TaskUploader(QString token, QObject *parent);

    bool uploadTask(BackupTask *task, QFile *archive);

public slots:
    void stop();

signals:
    void finished(int code, QString info);	//new
    void onError(int code, QString errorMessage);			//new
    void uploadFinished();
    void uploadProgress(qint64 sent, qint64 total);		//emit upload progress

private:
    void initConnections();

private:
    YDAPI *yd;
};

#endif // TASKUPLOADER_H

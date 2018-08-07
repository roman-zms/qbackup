#ifndef TASKCOMPRESSOR_H
#define TASKCOMPRESSOR_H

#include "compressorwrapper.h"

#include <QObject>

#include <backuptask/backuptask.h>

class TaskCompressor : public QObject
{
    Q_OBJECT
public:
    explicit TaskCompressor(QObject *parent = nullptr);
    bool compressTask(BackupTask *task);
    void stop();

    QFile *getLastAcrhive() const;

signals:
    void onCompressError(QString error);
    void onCompressSucces();
    void compressProgress(qint64 done, qint64 total);

private:
    void initSignals();
    void setLastArciveFile(QString fileName);
    static QString genArchiveName(BackupTaskSpecs *specs);

private:
    CompressorWrapper *compressor;
    QFile *lastAcrhive;
};

#endif // TASKCOMPRESSOR_H

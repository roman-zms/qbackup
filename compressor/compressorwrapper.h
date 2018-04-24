#ifndef COMPRESSORWRAPPER_H
#define COMPRESSORWRAPPER_H

#include <QObject>

#include "compressor.h"

class CompressorWrapper : public QObject
{
    Q_OBJECT
public:
    explicit CompressorWrapper(QObject *parent = nullptr);

signals:
    void onCompressError(QString error);
    void onCompressDirSucces();
    void compressProgress(qint64 done, qint64 total);

public slots:
    void compressDir(QString inputDir, QString archiveFile);
    void stop();

private:
    Compressor *compressor;
    QThread *thread;
};

#endif // COMPRESSORWRAPPER_H

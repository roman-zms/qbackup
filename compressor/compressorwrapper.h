#ifndef COMPRESSORWRAPPER_H
#define COMPRESSORWRAPPER_H

#include <QObject>

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
};

#endif // COMPRESSORWRAPPER_H

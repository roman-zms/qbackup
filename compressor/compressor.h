#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <QObject>
#include <QDir>

#include <quazip5/quazip.h>

class Compressor : public QObject
{
    Q_OBJECT
public:
    explicit Compressor(QObject *parent = nullptr);
    void compressDir(QString dir, QString archiveFile);

    void setData(QString dir, QString archiveFile);

    static qint64 getTotalSize(QString dir);

signals:
    void onCompressError(QString error);
    void onCompressDirSucces();
    void compressProgress(qint64 done, qint64 total);

public slots:
    void start();
//    void stop();

private:
    QString folderPath;
    QString archiveFile;

    qint64 totalSize;
    qint64 compressedSize;

    void compressDir(QuaZip *zip, QString inDir, QString outDir);
    void compressFile(QuaZip *zip, QString fileToCompress, QString relativeFileName);
    bool copyData(QIODevice &inFile, QIODevice &outFile);
};

#endif // COMPRESSOR_H

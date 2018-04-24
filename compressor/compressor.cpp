#include "compressor.h"

#ifdef Q_OS_WIN32
#include <quazip/quazipfile.h>
#endif

#ifdef Q_OS_LINUX
#include <quazip5/quazipfile.h>
#endif

Compressor::Compressor(QObject *parent) : QObject(parent)
{
    stop = false;
}

void Compressor::compressDir(QString dir, QString archiveFile)
{
    if(!QDir(dir).exists()){
        emit onCompressError("Directory not exist");
        return;
    }

    totalSize = Compressor::getTotalSize(dir);
    compressedSize = 0;

    QuaZip zip(archiveFile);

#ifdef Q_OS_WIN32
    zip.setFileNameCodec("IBM866");
#endif

    QDir().mkpath(QFileInfo(archiveFile).absolutePath());

    if(zip.open(QuaZip::mdCreate) == false){
        QFile(archiveFile).remove();
        emit onCompressError("Error creating file");
        return;
    }

    this->compressDir(&zip, dir, dir);

    zip.close();
    if(zip.getZipError()!=0){
        QFile::remove(archiveFile);
        emit onCompressError("Zip file error");
        return;
    }

    emit onCompressDirSucces();
}

void Compressor::setData(QString dir, QString archiveFile)
{
    this->folderPath = dir;
    this->archiveFile = archiveFile;
}

qint64 Compressor::getTotalSize(QString dir)
{
    qint64 size = 0;
    QDir directory(dir);
    QFileInfoList dirs = directory.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (QFileInfo dirInfo, dirs) {
        size += getTotalSize(dirInfo.absoluteFilePath());
    }
    QFileInfoList files = directory.entryInfoList(QDir::Files);
    foreach(QFileInfo fileInfo, files){
        size += fileInfo.size();
    }
    return size;
}

void Compressor::start()
{
    this->compressDir(folderPath, archiveFile);
}

void Compressor::stop()
{
    stop = true;
    folderPath = "";
    archiveFile = "";

    totalSize =0;
    compressedSize =0;

    this->deleteLater();
}

void Compressor::compressDir(QuaZip *zip, QString inDir, QString outDir)
{
    if(stop) {
        return;
    }
    if(!zip){
        emit onCompressError("API error");
        return;
    }
    if(zip->getMode() != QuaZip::mdAppend &&
       zip->getMode() != QuaZip::mdAdd &&
       zip->getMode() != QuaZip::mdCreate)
    {
        emit onCompressError("API mode error");
        return;
    }
    QDir directory(inDir);
    if(directory.exists() == false){
        emit onCompressError("Directory doesn't exist");
        return;
    }

    QDir zipDirectory(outDir);

    QString relativePrefix = zipDirectory.dirName() + QDir::separator();

    if(inDir != outDir) {
        QuaZipFile dirZipFile(zip);

        if(!dirZipFile.open(
               QIODevice::WriteOnly,
               QuaZipNewInfo(relativePrefix + zipDirectory.relativeFilePath(inDir) + QDir::separator(), inDir), 0, 0, 0))
        {
            emit onCompressError("Write error");
            return;
        }
        dirZipFile.close();
    } else {
        //QuaZipFile dirZipFile(zip);

        //if(!dirZipFile.open(
        //       QIODevice::WriteOnly,
        //       QuaZipNewInfo(relativePrefix + zipDirectory.dirName(), inDir), 0, 0, 0))
        //{
        //    emit onCompressError("Write error");
        //    return;
        //}
        //dirZipFile.close();
    }

    QFileInfoList subDirs = directory.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);
    foreach(QFileInfo subDir, subDirs){
        compressDir(zip, subDir.absoluteFilePath(), outDir);
    }

    QFileInfoList files = directory.entryInfoList(QDir::Files);
    foreach(QFileInfo file, files){
        //if(file.isFile() == false || file.absoluteFilePath() == zip->getZipName()) continue;
        if(file.isFile() || file.absoluteFilePath() != zip->getZipName()) {
            QString fileName = zipDirectory.relativeFilePath(file.absoluteFilePath());
            compressFile(zip, file.absoluteFilePath(), relativePrefix + fileName);
        }
    }
}

bool Compressor::copyData(QIODevice &inFile, QIODevice &outFile)
{
    while (!inFile.atEnd()){
        if(stop) {
            return false;
        }
        char buff[4096];
        qint64 readLen = inFile.read(buff, 4096);
        if(readLen <= 0){
            return false;
        }
        if(outFile.write(buff, readLen) != readLen){
            return false;
        }
        compressedSize += readLen;
        emit compressProgress(compressedSize, totalSize);
    }

    return true;
}

void Compressor::compressFile(QuaZip *zip, QString fileToCompress, QString relativeFileName)
{
    if(stop) return;
    if(!zip){
        emit onCompressError("API error");
        return;
    }
    if(zip->getMode() != QuaZip::mdAppend &&
       zip->getMode() != QuaZip::mdAdd &&
       zip->getMode() != QuaZip::mdCreate) {
        emit onCompressError("API mode error");
        return;
    }

    QFile inFile;
    inFile.setFileName(fileToCompress);
    if(inFile.open(QFile::ReadOnly) == false){
        emit onCompressError("Read error");
        return;
    }

    QuaZipFile outFile(zip);
    if(outFile.open(QuaZipFile::WriteOnly, QuaZipNewInfo(relativeFileName, inFile.fileName())) == false){
        emit onCompressError("Write error");
        return;
    }

    //zipping
    if(!copyData(inFile, outFile) || outFile.getZipError()!=UNZ_OK){
        emit onCompressError("Compress error");
        return;
    }

    outFile.close();
    if(outFile.getZipError()!=UNZ_OK){
        emit onCompressError("Zip file error");
        return;
    }
    inFile.close();
}

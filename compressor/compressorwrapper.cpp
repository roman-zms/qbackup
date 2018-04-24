
#include "compressorwrapper.h"
#include <QThread>

CompressorWrapper::CompressorWrapper(QObject *parent) : QObject(parent)
{

}

void CompressorWrapper::compressDir(QString inputDir, QString archiveFile)
{
    compressor = new Compressor();
    compressor->setData(inputDir, archiveFile);

    thread = new QThread();
    compressor->moveToThread(thread);

    //connect(thread, &QThread::started, this, [=](){
    //    compressor->compressDir(inputDir, archiveFile);
    //});
    connect(thread, &QThread::started, compressor, &Compressor::start);

    connect(compressor, &Compressor::compressProgress, this, &CompressorWrapper::compressProgress);

    connect(compressor, &Compressor::onCompressDirSucces, this, &CompressorWrapper::onCompressDirSucces);
    connect(compressor, &Compressor::onCompressDirSucces, this, [=](){
        compressor->deleteLater();

        thread->quit();
    //    thread->deleteLater();
    });

    connect(compressor, &Compressor::onCompressError, this, &CompressorWrapper::onCompressError);
    connect(compressor, &Compressor::onCompressError, this, [=](){
        compressor->deleteLater();
        thread->quit();
    //    thread->deleteLater();
    });

    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}

void CompressorWrapper::stop()
{
    compressor->stop();
    thread->terminate();

}

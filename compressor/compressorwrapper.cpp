
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

    connect(thread, &QThread::started, compressor, &Compressor::start);

    connect(compressor, &Compressor::compressProgress, this, &CompressorWrapper::compressProgress);

    connect(compressor, &Compressor::onCompressDirSucces, this, &CompressorWrapper::onCompressDirSucces);
    connect(compressor, &Compressor::onCompressDirSucces, this, [=](){
        thread->quit();
    //    thread->deleteLater();
    });

    connect(compressor, &Compressor::onCompressError, this, &CompressorWrapper::onCompressError);
    connect(compressor, &Compressor::onCompressError, this, [=](){
        thread->quit();
    //    thread->deleteLater();
    });

    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    connect(thread, &QThread::finished, compressor, &Compressor::deleteLater);

    thread->start();
}

void CompressorWrapper::stop()
{
    compressor->stop();
    compressor->deleteLater();
    disconnect(compressor, 0, 0, 0);

    thread->terminate();
    thread->wait();
    thread->deleteLater();
}

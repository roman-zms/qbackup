#include <QDebug>
#include <QDir>

#include "taskcompressor.h"

TaskCompressor::TaskCompressor(QObject *parent) : QObject(parent),
    compressor(new CompressorWrapper(this))
{
    initSignals();
}

bool TaskCompressor::compressTask(BackupTask *task)
{
    QString archiveName = TaskCompressor::genArchiveName(task->specs);
    qDebug() << archiveName;
    setLastArciveFile(archiveName);

    QString compressingDirectory = task->specs->getPathFrom();

    if (QDir(compressingDirectory).isReadable()) {
        compressor->compressDir(compressingDirectory, archiveName);
        return true;
    } else
        return false;
}

void TaskCompressor::initSignals()
{
    connect(compressor, &CompressorWrapper::onCompressError,
            this, &TaskCompressor::onCompressError);
    connect(compressor, &CompressorWrapper::onCompressDirSucces,
            this, &TaskCompressor::onCompressSucces);
    connect(compressor, &CompressorWrapper::compressProgress,
            this, &TaskCompressor::compressProgress);
}

void TaskCompressor::setLastArciveFile(QString fileName)
{
    if (lastAcrhive != nullptr) {
        lastAcrhive->deleteLater();
    }

    lastAcrhive = new QFile(fileName);
}

QString TaskCompressor::genArchiveName(BackupTaskSpecs *specs)
{
    QString archiveName = specs->getPathTo() + QDir::separator() +
                    specs->getName() + "_" + QDate::currentDate().toString("dd.MM.yyyy");

    if (QFile(archiveName + ".zip").exists()) {
        archiveName.append("(%1)");

        int index = 1;
        while (QFile(archiveName.arg(index) + ".zip").exists())
            index++;

        archiveName = archiveName.arg(index);
    }

    archiveName.append(".zip");
    return archiveName;
}

QFile *TaskCompressor::getLastAcrhive() const
{
    return lastAcrhive;
}


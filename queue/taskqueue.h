#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include <QWidget>
#include <QPair>
#include <QTreeWidgetItem>
#include <QDir>

#include <backuptask/backuptask.h>

#include "progressbardelegate.h"
#include "backuptask/backuptaskspecs.h"
#include "compressor/compressorwrapper.h"
#include "uploader/ydapi.h"

namespace Ui {
class TaskQueue;
}

class TaskQueue : public QWidget
{
    Q_OBJECT

public:
    explicit TaskQueue(QWidget *parent = nullptr);
    void addTask(BackupTask *task);
    ~TaskQueue();

public slots:
    void start();

private slots:
    void compress();
    void upload();

    void stop();
    void clear();

    void onCompressingError(QString message);
    void onUploadingError(int code, QString message);

    void updateTaskProgressBar(qint64 done, qint64 total);
    void updateTotalProgressBar();

    void on_startButton_clicked();

    void on_stopButton_clicked();

    void on_clearButton_clicked();

private:
    void init();
    QString genArchiveName(BackupTaskSpecs *task);

    Ui::TaskQueue *ui;

    typedef enum {
        compressing,
        uploading,
        nothing
    } OperationType;

    QList< QPair<BackupTaskSpecs*, QTreeWidgetItem*> > taskList;
    QPair<BackupTaskSpecs*, QTreeWidgetItem*> currentTask;

    int currentIndex;
    double completedOperations;
    double numberOfOperations;

    QString currentArchiveName;

    OperationType currentOperation;

    CompressorWrapper *compressor;
    YDAPI *yd;

};

#endif // TASKQUEUE_H

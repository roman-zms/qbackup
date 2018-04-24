#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include <QDialog>
#include <QPair>
#include <QTreeWidgetItem>
#include <QDir>

#include "progressbardelegate.h"
#include "backuptask/backuptaskspecs.h"
#include "compressor/compressorwrapper.h"
#include "uploader/ydapi.h"

namespace Ui {
class TaskQueue;
}

class TaskQueue : public QDialog
{
    Q_OBJECT

public:
    explicit TaskQueue(QWidget *parent = 0);
    void addTask(BackupTaskSpecs *taskSpecs);
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
    int completedOperations;
    int numberOfOperations;

    QString currentArchiveName;

    OperationType currentOperation;

    CompressorWrapper *compressor;
    YDAPI *yd;

};

#endif // TASKQUEUE_H

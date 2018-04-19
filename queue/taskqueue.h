#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include <QDialog>
#include <QPair>
#include <QTreeWidgetItem>
#include <QDir>

#include "progressbardelegate.h"
#include "backuptask/backuptaskspecs.h"
#include "compressor/compressorwrapper.h"

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

private slots:
    void start();
    void compress();
    void upload();

    void stop();
    void clear();

    void updateTaskProgressBar(qint64 done, qint64 total);

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

    OperationType currentOperation;

    CompressorWrapper *compressor;
};

#endif // TASKQUEUE_H

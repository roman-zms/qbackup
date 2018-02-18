#ifndef BACKUPTASK_H
#define BACKUPTASK_H

#include <QObject>
#include <QSettings>

class BackupTask : public QObject
{
    Q_OBJECT
public:
    explicit BackupTask(QString name, QObject *parent = nullptr);
    ~BackupTask();
    
    QString getPathFrom() const;
    void setPathFrom(const QString &value);

    QString getPathTo() const;
    void setPathTo(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    bool getAutoBackup() const;
    void setAutoBackup(bool value);

    bool getUpload() const;
    void setUpload(bool value);

private:
    bool initTask();
    bool saveTask();

    QString name;
    
    QString pathFrom;
    QString pathTo;
    
    bool autoBackup;
    bool upload;

    QSettings *settings;
};

#endif // BACKUPTASK_H

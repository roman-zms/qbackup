#ifndef BACKUPTASKSPECS_H
#define BACKUPTASKSPECS_H

#include <QObject>

class BackupTaskSpecs : public QObject
{
    Q_OBJECT
public:
    explicit BackupTaskSpecs(QString name, QObject *parent = nullptr);

    QString getName() const;

    QString getPathFrom() const;
    void setPathFrom(const QString &value);

    QString getPathTo() const;
    void setPathTo(const QString &value);

    bool getAutoBackup() const;
    void setAutoBackup(bool value);

    bool getUpload() const;
    void setUpload(bool value);

signals:

public slots:
private:
    QString name;

    QString pathFrom;
    QString pathTo;

    bool autoBackup;
    bool upload;

};

#endif // BACKUPTASKSPECS_H

#ifndef NSTATEFACTORY_H
#define NSTATEFACTORY_H

#include <QObject>

class NStateFactory : public QObject
{
    Q_OBJECT
public:
    explicit NStateFactory(QObject *parent = nullptr);

signals:

public slots:
};

#endif // NSTATEFACTORY_H
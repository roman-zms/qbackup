#ifndef TIMEDMESSAGEBOX_H
#define TIMEDMESSAGEBOX_H

#include <QMessageBox>
#include <QTimer>
#include <QPushButton>

class TimedMessageBox : public QMessageBox
{
    Q_OBJECT
public:
    TimedMessageBox(int timeoutInSeconds, Icon icon, const QString &title, const QString &text,
                StandardButtons buttons = NoButton, QWidget *parent = Q_NULLPTR,
                Qt::WindowFlags flags = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    void showEvent(QShowEvent *event);

private slots:
    void timerUpdate();

private:
    int m_timeout;
    QString m_text;
    QTimer *m_timer;
};

#endif // TIMEDMESSAGEBOX_H

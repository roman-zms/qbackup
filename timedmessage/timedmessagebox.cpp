#include "timedmessagebox.h"
#include <QMessageBox>
#include <QTimer>

TimedMessageBox::TimedMessageBox(
        int timeoutInSeconds, QMessageBox::Icon icon, const QString &title,
        const QString &text, QMessageBox::StandardButtons buttons, QWidget *parent,
        Qt::WindowFlags flags
    ) : QMessageBox(icon, title, text, buttons, parent, flags),
    m_timeout(timeoutInSeconds),
    m_text(text),
    m_timer(new QTimer(this))
{
    m_timer->setInterval(1000);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
}

void TimedMessageBox::showEvent(QShowEvent *event)
{
    QMessageBox::showEvent(event);
    timerUpdate();
    m_timer->start();
}

void TimedMessageBox::timerUpdate()
{
    if(--m_timeout >= 0){
        this->setText(m_text.arg(m_timeout));
    } else {
        m_timer->stop();
        if(!(this->defaultButton())){
            qCritical("Need def button");
            return;
        }

        this->defaultButton()->animateClick();
    }
}

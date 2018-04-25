#ifndef GENERALSETTINGS_H
#define GENERALSETTINGS_H

#include <QDialog>

namespace Ui {
class GeneralSettings;
}

class GeneralSettings : public QDialog
{
    Q_OBJECT

public:
    explicit GeneralSettings(QWidget *parent = 0);
    ~GeneralSettings();

private slots:
    void on_getTokenButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::GeneralSettings *ui;

    void save();
    void load();
};

#endif // GENERALSETTINGS_H

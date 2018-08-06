#include "generalsettings.h"
#include "ui_generalsettings.h"

#include <QCoreApplication>
#include <QDesktopServices>
#include <QDir>
#include <QSettings>
#include <QUrl>

GeneralSettings::GeneralSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GeneralSettings)
{
    ui->setupUi(this);
    load();
}

GeneralSettings::~GeneralSettings()
{
    delete ui;
}

void GeneralSettings::on_getTokenButton_clicked()
{
    QString link = "https://oauth.yandex.ru/authorize?response_type=token&client_id=b646ea711501461cb0cdae42f6a673ee";
    QDesktopServices::openUrl(QUrl(link));
}

void GeneralSettings::on_buttonBox_accepted()
{
    this->save();
    this->accept();
}

void GeneralSettings::save()
{
    QSettings settings;
    settings.setValue("AutoStart", ui->autoStartCheckBox->isChecked());
    settings.setValue("Token", ui->tokenLineEdit->text());
}

void GeneralSettings::load()
{
    QSettings settings;
    ui->autoStartCheckBox->setChecked(settings.value("AutoStart").toBool());
    ui->tokenLineEdit->setText(settings.value("Token").toString());
}

void GeneralSettings::on_autoStartCheckBox_toggled(bool checked)
{
    QSettings settings;
    settings.setValue("AutoStart", checked);
#ifdef Q_OS_WIN32
    if(checked){
        QSettings setting("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
                          QSettings::NativeFormat);
        setting.setValue(QCoreApplication::applicationName(),
                         QDir::toNativeSeparators(QCoreApplication::applicationFilePath()) + " MINIMIZE");
        setting.sync();
    } else {
        QSettings setting("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
                          QSettings::NativeFormat);
        setting.remove(QCoreApplication::applicationName());
        setting.sync();
    }
#endif

}

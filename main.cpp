#include "mainwindow/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("qBackup");
    QCoreApplication::setOrganizationName("Monkeys");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

#include "mainwindow/mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QLibraryInfo>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("qBackup");
    QCoreApplication::setOrganizationName("Monkeys");

    QApplication a(argc, argv);

#ifdef Q_OS_WIN32
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("IBM866"));
#endif

    QTranslator *qtTrans = new QTranslator;
    qtTrans->load("qt_"+QLocale::system().name(),
                QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    qApp->installTranslator(qtTrans);

    QTranslator *translator = new QTranslator;
    QString fileTr = QApplication::applicationDirPath()+
            QDir::separator()+"translations"+QDir::separator()+QLocale::system().name();
    if(!translator->load(fileTr))
        qApp->exit();
    else
        qApp->installTranslator(translator);

    MainWindow w;

    if(argc > 1){
        if (QString(argv[1]) == "MINIMIZE")
            w.hide();
    } else {
        w.show();
    }

    return a.exec();
}

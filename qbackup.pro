#-------------------------------------------------
#
# Project created by QtCreator 2018-02-17T15:01:45
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qbackup
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32 {
    INCLUDEPATH += D:/Qt/quazip/include
    DEPENDPATH += D:/Qt/quazip/include
    LIBS += -LD:/Qt/quazip/lib/ -lquazip
} else {
    LIBS += -lquazip5
}


SOURCES += \
        main.cpp \ 
    mainwindow/mainwindow.cpp \
    backuptask/backuptask.cpp \
    mainwindow/tasksettings/tasksettings.cpp \
    backuptask/backuptaskspecs.cpp \
    backuptask/taskschedule.cpp \
    queue/taskqueue.cpp \
    queue/progressbardelegate.cpp \
    compressor/compressor.cpp \
    compressor/compressorwrapper.cpp \
    uploader/ydapi.cpp \
    generalsettings/generalsettings.cpp

FORMS += \
    mainwindow/mainwindow.ui \
    mainwindow/tasksettings/tasksettings.ui \
    queue/taskqueue.ui \
    generalsettings/generalsettings.ui

HEADERS += \
    mainwindow/mainwindow.h \
    backuptask/backuptask.h \
    mainwindow/tasksettings/tasksettings.h \
    backuptask/backuptaskspecs.h \
    backuptask/taskschedule.h \
    queue/taskqueue.h \
    queue/progressbardelegate.h \
    compressor/compressor.h \
    compressor/compressorwrapper.h \
    uploader/ydapi.h \
    generalsettings/generalsettings.h

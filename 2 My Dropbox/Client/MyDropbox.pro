#-------------------------------------------------
#
# Project created by QtCreator 2015-02-20T22:58:21
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyDropbox
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    home.cpp \
    Ufunctions.cpp \
    client.cpp \
    clientUtility.cpp \
    File.cpp \
    oldversion.cpp \
    logData.cpp \
    commonUtility.cpp

HEADERS  += mainwindow.h \
    home.h \
    Ufunctions.h \
    client.h \
    MyDefines.h \
    structures.h \
    clientUtility.h \
    File.h \
    oldversion.h \
    logData.h \
    commonUtility.h

FORMS    += mainwindow.ui \
    home.ui \
    oldversion.ui

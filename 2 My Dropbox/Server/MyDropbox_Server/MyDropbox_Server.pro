#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T17:19:55
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyDropbox_Server
TEMPLATE = app


SOURCES +=\
        client.cpp \
    user.cpp \
    serverUtility.cpp \
    server.cpp

HEADERS  += client.h \
    user.h \
    MyDefines.h \
    server.h \
    serverUtility.h \
    structures.h

#-------------------------------------------------
#
# Project created by QtCreator 2013-11-09T02:51:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GPIO2Serial
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    thread.cpp

HEADERS  += mainwindow.h \
    myevent.h \
    thread.h

FORMS    += mainwindow.ui

CONFIG += thread

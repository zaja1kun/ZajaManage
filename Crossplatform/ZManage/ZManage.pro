#-------------------------------------------------
#
# Project created by QtCreator 2015-04-15T00:11:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ZManage
CONFIG += c++11


TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD/../../Linux/Logics
DEPENDPATH += $$PWD/../../Linux/Logics

unix:!macx: LIBS += -L$$PWD/../../Bin/Debug/ -lZMUnixLogics

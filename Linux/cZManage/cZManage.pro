#-------------------------------------------------
#
# Project created by QtCreator 2015-04-05T17:31:40
#
#-------------------------------------------------

QT       -= gui

TARGET = cZManage
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app

SOURCES += main.cpp

INCLUDEPATH += $$PWD/../Logics
DEPENDPATH += $$PWD/../Logics

unix:!macx: LIBS += -L$$PWD/../../Bin/Debug/ -lZMUnixLogics

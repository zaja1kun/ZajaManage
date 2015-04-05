#-------------------------------------------------
#
# Project created by QtCreator 2015-04-05T17:35:00
#
#-------------------------------------------------

TEMPLATE    = lib
DESTDIR     = /usr/lib/#./Out/#/usr/lib/
QT          -= gui
SOURCES     = logics.cpp \
    procinfo.cpp \
    threadinfo.cpp

HEADERS     = logics.h \
    procinfo.h \
    threadinfo.h

TARGET      = logics
CONFIG      += c++11

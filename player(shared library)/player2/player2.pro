#-------------------------------------------------
#
# Project created by QtCreator 2015-06-09T02:29:52
#
#-------------------------------------------------

QT       -= gui

TARGET = player2
TEMPLATE = lib

DEFINES += PLAYER2_LIBRARY

SOURCES += player2.cpp

HEADERS += player2.h\
        player2_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

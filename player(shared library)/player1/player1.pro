#-------------------------------------------------
#
# Project created by QtCreator 2015-06-08T16:26:25
#
#-------------------------------------------------

QT       -= gui

TARGET = player1
TEMPLATE = lib

DEFINES += PLAYER1_LIBRARY

SOURCES += player1.cpp

HEADERS += player1.h\
        player1_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

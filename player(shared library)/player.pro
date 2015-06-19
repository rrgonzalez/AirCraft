#-------------------------------------------------
#
# Project created by QtCreator 2015-06-06T05:46:19
#
#-------------------------------------------------

QT       += core widgets declarative

TARGET = player
TEMPLATE = lib

DEFINES += PLAYER_LIBRARY

SOURCES += player.cpp

HEADERS += player.h\
        player_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

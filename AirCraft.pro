TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    classes/computer-vs-computer.cpp \
    classes/person-vs-computer.cpp

RESOURCES += qml.qrc \
    resources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

OTHER_FILES +=

HEADERS += \
    classes/computer-vs-computer.h \
    classes/person-vs-computer.h

unix|win32: LIBS += -L$$PWD/dlls/player1/ -lplayer1

INCLUDEPATH += $$PWD/dlls/player1
DEPENDPATH += $$PWD/dlls/player1

unix|win32: LIBS += -L$$PWD/dlls/player2/ -lplayer2

INCLUDEPATH += $$PWD/dlls/player2
DEPENDPATH += $$PWD/dlls/player2

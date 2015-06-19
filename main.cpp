#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QMessageBox>

#include "classes/computer-vs-computer.h"
#include "classes/person-vs-computer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<ComputerVsComputer>("cu.uci.fac5.PcVsPC", 1, 0, "PcVsPc");
    qmlRegisterType<PersonVsComputer>("cu.uci.fac5.PersonVsPC", 1, 0, "PersonVsPc");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}

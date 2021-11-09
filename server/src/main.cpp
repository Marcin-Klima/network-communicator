#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Server.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Server server;

    engine.rootContext()->setContextProperty("server", &server);
    engine.load(QUrl(QStringLiteral("qrc:\\main.qml")));

    return app.exec();
}
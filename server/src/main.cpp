#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <boost/log/trivial.hpp>

#include "Server.h"

int main(int argc, char** argv)
{
    BOOST_LOG_TRIVIAL(info) << "Running application";

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Server server;
    engine.rootContext()->setContextProperty("server", &server);

#ifdef SYS_WINDOWS
    engine.load(QUrl(QStringLiteral("qrc:\\main.qml")));
#elif SYS_LINUX
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
#endif

    return app.exec();
}
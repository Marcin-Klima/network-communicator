//
// Created by Marcin on 1/6/2022.
//

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <boost/log/trivial.hpp>

#include "Frontend.h"
#include "Server.h"

void Frontend::run(int argc, char** argv, Server& server)
{
    QApplication application(argc, argv);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("server", &server);

    qRegisterMetaType<size_t>("size_t");

#ifdef SYS_WINDOWS
    engine.load(QUrl(QStringLiteral("qrc:\\main.qml")));
#elif SYS_LINUX
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
#endif

    application.exec();
}

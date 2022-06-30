//
// Created by Marcin on 1/6/2022.
//

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <spdlog/spdlog.h>

#include "Frontend.h"
#include "Server.h"

void Frontend::run(int argc, char** argv, Server& server)
{
    QApplication application(argc, argv);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("backend", &server);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &application,
            [&application](QObject* object, [[maybe_unused]] const QUrl& objUrl) {
                if (object == nullptr)
                {
                    spdlog::error("Error while loading frontend object tree: " + objUrl.toString().toStdString());
                    application.exit(-100);
                }
            }, Qt::QueuedConnection);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    application.exec();
}

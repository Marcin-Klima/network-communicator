//
// Created by Marcin on 1/6/2022.
//

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <boost/log/trivial.hpp>

#include "Frontend.h"

Frontend::Frontend(int argc, char** argv, Backend& backend) : _application(argc, argv), _backend(backend)
{

}

void Frontend::run()
{
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("backend", &_backend);

    connect(&engine, &QQmlApplicationEngine::objectCreated, this, &Frontend::mainWindowLoaded);
    BOOST_LOG_TRIVIAL(info) << "loading qml object tree";
#ifdef SYS_WINDOWS
    engine.load(QUrl(QStringLiteral("qrc:\\main.qml")));
#elif SYS_LINUX
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
#endif
    BOOST_LOG_TRIVIAL(info) << "error!";
}

void Frontend::mainWindowLoaded(QObject* object, [[maybe_unused]] const QUrl& url)
{
    if(object != nullptr)
    {
        BOOST_LOG_TRIVIAL(info) << "object tree has been loaded";
        _backend.run(); //works on separate thread!
        _application.exec();
    }
    else
    {
        BOOST_LOG_TRIVIAL(error) << "object tree has not loaded correctly!";
    }
}



//
// Created by Marcin on 1/6/2022.
//

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <boost/log/trivial.hpp>

#include "Frontend.h"

Frontend::Frontend()
{

}

void Frontend::run(int argc, char** argv, Backend& backend)
{
    QApplication application(argc, argv);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("backend", &backend);

    BOOST_LOG_TRIVIAL(info) << "loading qml object tree";
#ifdef SYS_WINDOWS
    engine.load(QUrl(QStringLiteral("qrc:\\main.qml")));
#elif SYS_LINUX
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
#endif
    application.exec();
}

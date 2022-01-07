//
// Created by Marcin on 1/6/2022.
//

#pragma once

#include <QObject>
#include <QApplication>
#include "Backend.h"

class Frontend : public QObject
{
    Q_OBJECT

public:
    Frontend(int argc, char** argv, Backend& backend);
    void run();

private slots:
    void mainWindowLoaded(QObject* object, const QUrl& url);

private:
    QApplication _application;
    Backend& _backend;
};

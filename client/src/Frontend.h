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
    Frontend();
    void run(int argc, char** argv, Backend& backend);

private slots:

private:
};

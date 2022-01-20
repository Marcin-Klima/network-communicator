//
// Created by Marcin on 1/6/2022.
//

#pragma once

#include "Server.h"
#include <QObject>

class Frontend : public QObject
{
    Q_OBJECT
public:
    void run(int argc, char** argv, Server& server);

private:

};

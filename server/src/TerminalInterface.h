//
// Created by Marcin on 8/10/2021.
//

#pragma once

#include <boost/thread/thread.hpp>
#include <boost/function.hpp>
#include "Server.h"

class TerminalInterface
{
public:
    TerminalInterface(Server *server = nullptr);

    ~TerminalInterface();

    void operator()();

    void Stop();

    void SetServer(Server *server);

    void PrintMessage(const std::string &message);

private:
    boost::thread _thread;
    boost::mutex _terminalMutex;

    std::string _currentCommand;
    bool _running;
    const std::map<std::string, boost::function<void()>> commandMap = {
            {"exit", boost::bind(&TerminalInterface::Stop, this)}
    };
    Server *_server;
};

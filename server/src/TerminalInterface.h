//
// Created by Marcin on 8/10/2021.
//

#pragma once

#include <boost/thread/thread.hpp>
#include <boost/function.hpp>

class Server;

class TerminalInterface
{
    friend class TerminalOutput;

public:
    TerminalInterface(Server *server);

    ~TerminalInterface();

    void Run();

    void operator()();

    void Stop();

private:
    void PrintMessage(const std::string &message);

    std::unique_ptr<boost::thread> _thread;
    boost::mutex terminalMutex;

    std::string _currentCommand;
    bool _running;
    const std::map<std::string, boost::function<void()>> commandMap = {
            {"exit", boost::bind(&TerminalInterface::Stop, this)}
    };

    Server *_server;
};

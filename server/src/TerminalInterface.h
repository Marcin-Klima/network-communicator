//
// Created by Marcin on 8/10/2021.
//

#pragma once

#include <boost/thread/thread.hpp>
#include <boost/function.hpp>

class Server;
class TerminalInterfaceServerMediator;

class TerminalInterface
{
public:
    TerminalInterface();

    ~TerminalInterface();

    void Run();

    void Stop();

    void SetMediator(TerminalInterfaceServerMediator* terminalInterfaceServerMediator);

    void PrintMessage(const std::string& message);

private:
    void ThreadLoop();

    std::unique_ptr<boost::thread> _thread;
    boost::mutex terminalMutex;

    std::string _currentCommand;
    bool _running;
    const std::map<std::string, boost::function<void()>> commandMap = {
            {"exit", boost::bind(&TerminalInterface::Stop, this)}
    };

    TerminalInterfaceServerMediator* _mediator;
};

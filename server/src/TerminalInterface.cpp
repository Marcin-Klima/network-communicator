//
// Created by Marcin on 8/10/2021.
//

#include <iostream>
#include "TerminalInterface.h"
#include <boost/function.hpp>

namespace
{
    constexpr auto COMMAND_PROMPT = "server_>>>";
}

TerminalInterface::TerminalInterface(Server *server) : _server(server)
{
}

TerminalInterface::~TerminalInterface()
{
}

void TerminalInterface::operator()()
{
    char character;

    while (_running) {
        terminalMutex.lock();
        std::cout << COMMAND_PROMPT;
        terminalMutex.unlock();

        while ((character = std::cin.get()) != '\n') {
            _currentCommand += character;
        }

        if (commandMap.find(_currentCommand) != commandMap.end()) {
            commandMap.at(_currentCommand)();
        }

        _currentCommand.clear();
    }
}

void TerminalInterface::Stop()
{
    _running = false;
}

void TerminalInterface::PrintMessage(const std::string &message)
{
    boost::lock_guard lock(terminalMutex);
    std::cout << '\r' << message << '\n';
    std::cout << COMMAND_PROMPT;
}

void TerminalInterface::Run()
{
    auto fun = boost::function<void()>(boost::ref(&TerminalInterface::Run));
    _thread = std::make_unique<boost::thread>(new boost::thread(fun));
}

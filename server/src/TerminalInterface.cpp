//
// Created by Marcin on 8/10/2021.
//

#include <iostream>
#include "TerminalInterface.h"

namespace
{
    constexpr auto COMMAND_PROMPT = "server>>>";
}

TerminalInterface::TerminalInterface(Server *server) :
        _thread(boost::ref(*this)),
        _server(server),
        _running(false)
{
}

TerminalInterface::~TerminalInterface()
{
    _thread.join();
}

void TerminalInterface::operator()()
{
    _running = true;
    char character;

    while (_running) {
        std::cout << COMMAND_PROMPT;

        while((character = std::cin.get()) != '\n') {
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
    if (_server != nullptr) {
        _server->Halt();
    }
}

void TerminalInterface::SetServer(Server *server)
{
    _server = server;
}

void TerminalInterface::PrintMessage(const std::string &message)
{
    boost::lock_guard lock(_terminalMutex);
    std::cout << '\n' << message << '\n';
    std::cout << COMMAND_PROMPT + _currentCommand;
}

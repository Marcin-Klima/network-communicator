//
// Created by Marcin on 8/10/2021.
//

#include <iostream>
#include "TerminalInterface.h"

namespace
{
    constexpr auto COMMAND_PROMPT = "server>>>";
}

TerminalInterface::TerminalInterface() :
        _thread(boost::ref(*this))
{
}

TerminalInterface::~TerminalInterface()
{
    _thread.join();
}

void TerminalInterface::operator()()
{
    std::string command;

    running = true;

    while (running) {
        std::cout << COMMAND_PROMPT;
        std::cin >> command;

        if (commandMap.find(command) != commandMap.end()) {
            commandMap.at(command)();
        }
    }
}

void TerminalInterface::Stop()
{
    running = false;
}





//
// Created by Marcin on 10/5/2021.
//

#pragma once

#include <string>

class Server;
class TerminalInterface;

class TerminalInterfaceServerMediator
{
    friend class Server;
    friend class TerminalInterface;

public:
    TerminalInterfaceServerMediator(Server* server, TerminalInterface* terminalInterface);

private:
    void RunServer();
    void PrintMessage(const std::string& string);
    void HaltServer();

    Server* _server;
    TerminalInterface* _terminalInterface;
};

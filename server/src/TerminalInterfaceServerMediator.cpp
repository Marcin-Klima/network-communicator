//
// Created by Marcin on 10/5/2021.
//

#include "TerminalInterfaceServerMediator.h"
#include "Server.h"

#include "TerminalInterface.h"

TerminalInterfaceServerMediator::TerminalInterfaceServerMediator(Server* server, TerminalInterface* terminalInterface) :
        _terminalInterface(terminalInterface),
        _server(server)
{
    _server->SetMediator(this);
    _terminalInterface->SetMediator(this);
}

void TerminalInterfaceServerMediator::RunServer()
{
    _server->Run();
}

void TerminalInterfaceServerMediator::PrintMessage(const std::string& string)
{
    _terminalInterface->PrintMessage(string);
}

void TerminalInterfaceServerMediator::HaltServer()
{
    _server->Halt();
}

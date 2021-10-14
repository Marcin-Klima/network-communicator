//
// Created by Marcin on 8/5/2021.
//

#include "Server.h"
#include "TerminalInterface.h"
//#include "TerminalInterfaceServerMediator.h"
#include <iostream>

int main()
{
    Server server;
    TerminalInterface terminalInterface;
    TerminalInterfaceServerMediator terminalInterfaceServerMediator(&server, &terminalInterface);

    terminalInterface.Run();
    server.Run();

    return 0;
}
//
// Created by Marcin on 8/5/2021.
//

#include "Server.h"
#include "TerminalInterface.h"

int main()
{
    Server server;
    TerminalInterface terminalInterface;

    server.SetTerminalInterface(&terminalInterface);
    terminalInterface.SetServer(&server);

    return server.Run();
}
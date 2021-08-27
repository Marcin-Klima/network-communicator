//
// Created by Marcin on 8/5/2021.
//

#include "Server.h"
#include "TerminalInterface.h"

int main()
{
    Server server;
//    TerminalInterface terminalInterface;

//    TerminalOutput terminalOutput(terminalInterface);
//    server.SetTerminalOutput(&terminalOutput);

    return server.Run();
}
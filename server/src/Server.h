//
// Created by Marcin on 8/10/2021.
//

#pragma once

#include <boost/asio.hpp>

#include <string>
#include "TerminalOutput.h"

using boost::asio::ip::tcp;

class Server
{
public:
    Server();

    int Run();

    void Halt();

    void SetTerminalOutput(TerminalOutput *terminalOutput);

private:
    void HandleNewConnection(boost::system::error_code errorCode, tcp::socket socket);

    void AcceptNewConnections(tcp::acceptor &acceptor);

    std::string makeDaytimeString();
    boost::asio::io_service ioService;
    TerminalOutput *terminalOutput;
    TerminalInterface terminalInterface;
};


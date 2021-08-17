//
// Created by Marcin on 8/10/2021.
//

#pragma once

#include <boost/asio.hpp>

#include <string>

using boost::asio::ip::tcp;

class TerminalInterface;

class Server
{
public:
    explicit Server(TerminalInterface *terminalInterface = nullptr);

    int Run();

    void Halt();

    void SetTerminalInterface(TerminalInterface *terminalInterface);

private:
    void HandleNewConnection(boost::system::error_code errorCode, tcp::socket socket);

    void AcceptNewConnections(tcp::acceptor &acceptor);

    std::string makeDaytimeString();

    boost::asio::io_service _ioService;
    TerminalInterface *_terminalInterface;
};

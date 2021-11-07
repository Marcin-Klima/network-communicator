//
// Created by Marcin on 8/10/2021.
//

#pragma once

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include <string>
#include <QObject>
#include "TerminalInterfaceServerMediator.h"


using boost::asio::ip::tcp;

class TerminalInterfaceServerMediator;

class Server : public QObject
{
    Q_OBJECT

public:
    Server();

    ~Server();

    int Run();

    void Halt();

    void SetMediator(TerminalInterfaceServerMediator* terminalInterfaceServerMediator);

private:
    void HandleNewConnection(boost::system::error_code errorCode, tcp::socket socket);

    void AcceptNewConnections(tcp::acceptor& acceptor);

    std::string makeDaytimeString();

    boost::asio::io_service ioService;
    TerminalInterfaceServerMediator* _mediator;
};

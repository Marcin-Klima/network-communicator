//
// Created by Marcin on 8/10/2021.
//

#include <iostream>
#include <ctime>
#include <boost/bind/bind.hpp>
#include <boost/bind/placeholders.hpp>

#include "Server.h"
#include "TerminalInterfaceServerMediator.h"

Server::Server()
{
}

int Server::Run()
{
    for(int i = 0; i < 10; ++i) {
        _mediator->PrintMessage("DUPA");
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }

    try {
        tcp::acceptor acceptor(ioService, tcp::endpoint(tcp::v4(), 13));

        AcceptNewConnections(acceptor);

        ioService.run();

        return 0;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;

        return -1;
    }
}

std::string Server::makeDaytimeString()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

void Server::HandleNewConnection(boost::system::error_code errorCode, tcp::socket socket)
{
    std::string message = makeDaytimeString();

    boost::system::error_code ignored_error;
    boost::asio::write(socket, boost::asio::buffer(message),
                       boost::asio::transfer_all(), ignored_error);
}

void Server::AcceptNewConnections(tcp::acceptor& acceptor)
{
    acceptor.async_accept([this, &acceptor](boost::system::error_code errorCode, tcp::socket socket) {
        HandleNewConnection(errorCode, std::move(socket));

        AcceptNewConnections(acceptor);
    });
}

void Server::Halt()
{
    ioService.stop();
}

Server::~Server()
{
}

void Server::SetMediator(TerminalInterfaceServerMediator* terminalInterfaceServerMediator)
{
    _mediator = terminalInterfaceServerMediator;
}

//
// Created by Marcin on 8/10/2021.
//

#include "Server.h"
#include <iostream>

#include <ctime>
#include <boost/bind/bind.hpp>
#include <boost/bind/placeholders.hpp>

Server::Server() : terminalInterface(this)
{

}

int Server::Run()
{
    try {
        tcp::acceptor acceptor(ioService, tcp::endpoint(tcp::v4(), 13));

        AcceptNewConnections(acceptor);

        ioService.run();

        return 0;
    }
    catch (std::exception &e) {
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
    if (terminalOutput != nullptr) {
        terminalOutput->Print("Client connected from: " +socket.remote_endpoint().address().to_string());
    }

    std::string message = makeDaytimeString();

    boost::system::error_code ignored_error;
    boost::asio::write(socket, boost::asio::buffer(message),
                       boost::asio::transfer_all(), ignored_error);
}

void Server::AcceptNewConnections(tcp::acceptor &acceptor)
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

void Server::SetTerminalOutput(TerminalOutput *terminalOutput)
{
    this->terminalOutput = terminalOutput;
}
//
// Created by Marcin on 8/10/2021.
//

#include "Server.h"
#include <iostream>
#include <ctime>
#include <boost/bind/bind.hpp>
#include <boost/bind/placeholders.hpp>

Server::Server()
{

}

void Server::Run()
{
    try {
        boost::asio::io_service ioService;
        tcp::acceptor acceptor(ioService, tcp::endpoint(tcp::v4(), 13));

        AcceptNewConnections(acceptor);

        ioService.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

std::string Server::makeDaytimeString()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

void Server::ConnectionAccept(boost::system::error_code errorCode, tcp::socket socket)
{
    std::string message = makeDaytimeString();

    boost::system::error_code ignored_error;
    boost::asio::write(socket, boost::asio::buffer(message),
                       boost::asio::transfer_all(), ignored_error);
}

void Server::AcceptNewConnections(tcp::acceptor &acceptor)
{
    acceptor.async_accept([this, &acceptor](boost::system::error_code errorCode, tcp::socket socket) {
        ConnectionAccept(errorCode, std::move(socket));

        AcceptNewConnections(acceptor);
    });
}

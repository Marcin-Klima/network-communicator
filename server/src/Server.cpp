//
// Created by Marcin on 8/10/2021.
//

#include "Server.h"
#include <boost/asio.hpp>
#include <iostream>

Server::Server() : _endpoint(tcp::v4(), 6969),
                   _acceptor(_io_context, _endpoint)
{

}

void Server::threadLoop()
{
    try {
        //run connectiojn acceptor
        acceptNewConnection();

        std::cout << "running io_context" << std::endl;
        _io_context.run();
    }
    catch (std::exception& exception) {
        std::cout << exception.what();
    }
}

Server::~Server()
{
}

void Server::halt()
{
}

void Server::receiveInputFromFrontent(const QString& input)
{
    QString command(input);
    std::cout << "command: " << command.toStdString() << std::endl;
    if (command.startsWith('/')) {
        command.remove(0, 1);
        if (command == "start") {
            threadLoop();
        }
        if (command == "halt") {
            _io_context.stop();
        }
    } else {

    }
}

void Server::acceptNewConnection()
{
    std::cout << "accepting new connection" << std::endl;
    _acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec) {
            std::cout << "client connected from: " << socket.remote_endpoint().address().to_string() << std::endl;
        }
        acceptNewConnection();
    });
}

// TODO: zrobić osobny wątek!!!
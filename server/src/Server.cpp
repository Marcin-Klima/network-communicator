//
// Created by Marcin on 8/10/2021.
//

#include "Server.h"
#include <boost/asio.hpp>
#include <iostream>

Server::Server() : _endpoint(tcp::v4(), 6969)
{

}

void Server::threadLoop()
{
    try
    {
        //run connectiojn acceptor

        _io_context.run();
    }
    catch(std::exception& exception)
    {
        std::cout << exception.what();
    }
}

Server::~Server()
{
    if(_thread != nullptr)
    {
        _thread->join();
    }
}

void Server::halt()
{
}

void Server::receiveInputFromFrontent([[maybe_unused]] const QString& input)
{
    QString command(input);
    if(command.startsWith('/'))
    {
        command.remove(0, 1);
        if(command == "start")
        {
            _thread = std::make_unique<boost::thread>(&Server::threadLoop, this);
        }
        if(command == "halt")
        {
            _io_context.stop();
        }
    }
    else
    {

    }
}

void Server::acceptNewConnection()
{
    tcp::acceptor acceptor(_io_context, _endpoint);
    acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket){
        if(!ec)
        {
            std::cout << "client connected from: " << socket.remote_endpoint().address().to_string() << std::endl;
        }
        acceptNewConnection();
    });
}

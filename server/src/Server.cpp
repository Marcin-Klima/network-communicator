//
// Created by Marcin on 8/10/2021.
//

#include "Server.h"

Server::Server()
{

}

void Server::start()
{
    _thread = std::make_unique<boost::thread>(&Server::threadLoop, this);
}

void Server::threadLoop()
{
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

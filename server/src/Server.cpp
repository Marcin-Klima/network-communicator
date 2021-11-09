//
// Created by Marcin on 8/10/2021.
//

#include "Server.h"

Server::Server()
{

}

void Server::start()
{
    _thread = std::make_unique<boost::thread>(&Server::run, this);
}

void Server::run()
{
    for(int i = 0; i < 5; ++i)
    {
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
        emit serverCreated();
    }
}

void Server::stop(QString& command)
{

}

Server::~Server()
{
    if(_thread != nullptr)
    {
        _thread->join();
    }
}

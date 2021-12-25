//
// Created by Marcin on 8/10/2021.
//

#include "Server.h"
#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

Server::Server() : _endpoint(tcp::v4(), 6969),
                   _acceptor(_io_context, _endpoint)
{

}

void Server::threadLoop()
{
    try {
        acceptNewConnection();

        _io_context.run();
    }
    catch (std::exception& exception) {
        BOOST_LOG_TRIVIAL(error) << "!!!EXCEPTION: " << exception.what();
    }
}

Server::~Server()
{
    if(_thread != nullptr && _thread->joinable())
    {
        _thread->join();
    }
}

void Server::startServer()
{
    _thread = std::make_unique<boost::thread>(&Server::threadLoop, this);
    emit serverStarted();
}

void Server::halt()
{
    if(!_io_context.stopped())
    {
        BOOST_LOG_TRIVIAL(info) << "Stopping server";
        _io_context.stop();
        emit serverStopped();
    }
}

void Server::receiveInputFromFrontend(const QString& input)
{
    QString command(input);
    BOOST_LOG_TRIVIAL(debug) << "User command: " << input.toStdString();
    if (command.startsWith('/')) {
        if (command == "/start") {
            startServer();
        }
        if (command == "/halt") {
            halt();
        }
    } else {

    }
}

void Server::acceptNewConnection()
{
    BOOST_LOG_TRIVIAL(trace) << "Accepting new connection";
    _acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec) {
            BOOST_LOG_TRIVIAL(info) << "Client connected from: " << socket.remote_endpoint().address().to_string();
        }
        acceptNewConnection();
    });
}

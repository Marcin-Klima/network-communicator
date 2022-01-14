//
// Created by Marcin on 8/10/2021.
//

#include "Server.h"
#include "Session.h"
#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

#include <memory>

Server::Server() : _endpoint(tcp::v4(), 6969),
                   _acceptor(_io_context, _endpoint)
{

}

void Server::threadLoop()
{
    try
    {
        acceptNewConnection();

        _io_context.run();
    }
    catch (std::exception& exception)
    {
        BOOST_LOG_TRIVIAL(error) << "!!!EXCEPTION: " << exception.what();
    }
}

Server::~Server()
{
    if (_thread != nullptr && _thread->joinable())
    {
        _thread->join();
    }
}

void Server::startServer()
{
    BOOST_LOG_TRIVIAL(info) << "starting server";
    _thread = std::make_unique<boost::thread>(&Server::threadLoop, this);
    emit serverStarted();
}

void Server::stopServer()
{
    if (!_io_context.stopped())
    {
        BOOST_LOG_TRIVIAL(info) << "Stopping server";
        _io_context.stop();
        emit serverStopped();
    }
}

void Server::receiveInputFromFrontend(const QString& input)
{
    QString command(input);
    if (command.startsWith('/'))
    {
        if (command == "/start")
        {
            startServer();
        }
        if (command == "/halt")
        {
            stopServer();
        }
    } else
    {

    }
}

void Server::acceptNewConnection()
{
    _acceptor.async_accept([this](boost::system::error_code ec, tcp::socket clientSocket) {
        if (!ec)
        {
            BOOST_LOG_TRIVIAL(info) << "client connected from ip address: "
                                    << clientSocket.remote_endpoint().address().to_v4().to_string();
            auto newSession = std::make_unique<Session>(*this, std::move(clientSocket));
            _sessions[newSession.get()] = std::move(newSession);
        }
        acceptNewConnection();
    });
}

void Server::closeSession(Session* session)
{
    BOOST_LOG_TRIVIAL(info) << "removing session";
    _sessions.erase(session);
}

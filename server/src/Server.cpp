//
// Created by Marcin on 8/10/2021.
//

#include "Server.h"
#include "Session.h"
#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

#include <memory>

Server::Server() : _endpoint(tcp::v4(), 6969),
                   _acceptor(_ioContext, _endpoint), _running(false)
{

}

void Server::startServer()
{
    if (!_running)
    {
        BOOST_LOG_TRIVIAL(info) << "Starting server";
        try
        {
            _running = true;
            _ioContext.restart();

            acceptNewConnection();
            boost::thread thread([this](){ this->_ioContext.run(); });
            emit serverStarted();

            thread.join();
        }
        catch (std::exception& exception)
        {
            BOOST_LOG_TRIVIAL(error) << "!!!EXCEPTION: " << exception.what();
        }
    }
}

void Server::stopServer()
{
    if (_running)
    {
        BOOST_LOG_TRIVIAL(info) << "Stopping server";
        _ioContext.stop();
        _sessions.clear();
        _running = false;
        emit serverStopped();
    }
}

void Server::receiveInputFromFrontend(const QString& input)
{
    QString command(input);

}

void Server::acceptNewConnection()
{
    _acceptor.async_accept([this](boost::system::error_code ec, tcp::socket clientSocket) {
        if (!ec)
        {
            BOOST_LOG_TRIVIAL(info) << "client connected from ip address: "
                                    << clientSocket.remote_endpoint().address().to_v4().to_string();
            auto clientSession = Session::create(this, std::move(clientSocket));
            _sessions.push_back(clientSession);
            clientSession->open();
            emit clientConnected();
        }
        acceptNewConnection();
    });
}

void Server::closeSession(std::shared_ptr<Session> session)
{
    _sessions.erase(std::find(_sessions.begin(), _sessions.end(), session));
    emit clientDisconnected();
}

void Server::testSlot()
{
    BOOST_LOG_TRIVIAL(info) << "TEST TEST";
}

void Server::processMessageFromClient(std::shared_ptr<Session> sender, std::string message)
{
    for(auto session : _sessions)
    {
        if(session != sender)
        {
            //todo: komunikacja pomiedzy sesjami!!!!

        }
    }
    emit printMessage(QString::fromStdString(message));
}

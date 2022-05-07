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
            _thread = std::make_unique<boost::thread>([this](){this->_ioContext.run();});
            emit serverStarted();
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
        _thread->join();
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
            std::lock_guard<std::mutex> lockGuard(_clientQueueMutex);
            _sessions.insert(clientSession);
            clientSession->open();
            emit clientConnected();
        }
        acceptNewConnection();
    });
}

void Server::closeSession(std::shared_ptr<Session> session)
{
    std::lock_guard<std::mutex> lockGuard(_clientQueueMutex);
    _sessions.erase(session);
    emit clientDisconnected();
}

void Server::testSlot()
{
    BOOST_LOG_TRIVIAL(info) << "TEST TEST";
}

void Server::sendOutMessage(const std::shared_ptr<Session>& sender, const std::string& message)
{
    //todo: determine max queue length and delete from front
    emit printMessage(QString::fromStdString(message));

    auto messagePointer = std::make_shared<std::string>(message);
    std::lock_guard lockGuard(_clientQueueMutex);
    _messageMap[messagePointer] = _sessions.size() - 1;
    for(const auto& session : _sessions)
    {
        if(session != sender)
        {
            session->dispatchMessage(messagePointer);
        }
    }
}

void Server::messageSubmittedToNetworkStack(const std::shared_ptr<Session>& sender, std::shared_ptr<std::string> message)
{
    BOOST_LOG_TRIVIAL(info) << "submitted in: " << sender;
    _messageMap[message]--;
    if(_messageMap[message] == 0)
    {
        BOOST_LOG_TRIVIAL(info) << "message submitted in all clients' sessions!";
        _messageMap.erase(message);
    }
}

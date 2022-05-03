//
// Created by waxta on 29.12.2021.
//

#include "Session.h"
#include <boost/log/trivial.hpp>
#include <boost/bind/bind.hpp>

#include <string>

Session::Session(Server* server, tcp::socket socket) :
        _server(server),
        _socket(std::move(socket))
{
    BOOST_LOG_TRIVIAL(debug) << "konstruktor";
}

void Session::open()
{
    awaitMessage();
}


void Session::awaitMessage()
{
    _socket.async_read_some(boost::asio::buffer(_data, MAX_MESSAGE_LENGTH),
                            boost::bind(&Session::awaitMessageHandler, shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

void Session::awaitMessageHandler(boost::system::error_code errorCode, size_t messageLength)
{
    if (!errorCode)
    {
        std::string message(_data, messageLength);
        BOOST_LOG_TRIVIAL(debug) << "client says: " << message;

        _server->sendOutMessage(shared_from_this(), message);
        awaitMessage();
    } else
    {
        BOOST_LOG_TRIVIAL(debug) << "reading error! error code: " << errorCode;
        stop();
    }
}

Session::~Session()
{
    BOOST_LOG_TRIVIAL(debug) << "session's destructor";
}

std::shared_ptr<Session> Session::create(Server* server, tcp::socket socket)
{
    return std::shared_ptr<Session>(new Session(server, std::move(socket)));
}

void Session::dispatchMessage(std::shared_ptr<std::string> message)
{
    bool isWriting = !_writeMessageQueue.empty();
    _writeMessageQueue.push_back(message);
    if (!isWriting)
    {
        startWriting();
    }
}

void Session::startWriting()
{
    auto buffer = boost::asio::buffer(_writeMessageQueue.front().get(), _writeMessageQueue.front()->length());
    boost::asio::async_write(_socket, buffer,
                             boost::bind(&Session::writeHandler, this, boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void Session::writeHandler(boost::system::error_code ec, std::size_t bytesTransferred)
{
    if (!ec)
    {
        _server->messageSubmittedToNetworkStack(shared_from_this(), _writeMessageQueue.front());
        _writeMessageQueue.pop_front();
        if (!_writeMessageQueue.empty())
        {
            startWriting();
        }
    } else
    {
        BOOST_LOG_TRIVIAL(error) << "Writing error! Error code: " << ec << " Bytes transferred: " << bytesTransferred;
        if (ec == boost::asio::error::eof)
        {
            BOOST_LOG_TRIVIAL(info) << "EOF";
        }
        stop();
    }
}

void Session::stop()
{
    _socket.close();
    _server->closeSession(shared_from_this());
}
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
    waitForMessage();
}


void Session::waitForMessage()
{
    //boost::bind has the ability to bind function with shared_poniter of T class as *this* pointer
    _socket.async_read_some(boost::asio::buffer(_data, MAX_MESSAGE_LENGTH),
                            boost::bind(&Session::readHandler, shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

void Session::readHandler(boost::system::error_code errorCode, size_t messageLength)
{
    if (!errorCode)
    {
        std::string message(_data, messageLength);
        BOOST_LOG_TRIVIAL(debug) << "client says: " << message;

        _server->processMessageFromClient(shared_from_this(), std::move(message));
        memset(_data, 0, MAX_MESSAGE_LENGTH);
        waitForMessage();
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

void Session::dispatchMessage(const std::string& message)
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
    boost::asio::async_write(_socket,
                             boost::asio::buffer(_writeMessageQueue.front(), _writeMessageQueue.front().length()),
                             boost::bind(&Session::writeHandler, this, boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void Session::writeHandler(boost::system::error_code ec, std::size_t bytesTransferred)
{
    if(!ec)
    {
        BOOST_LOG_TRIVIAL(debug) << "Writing ok!";
        _writeMessageQueue.pop_front();
        if(!_writeMessageQueue.empty())
        {
            startWriting();
        }
    }
    else
    {
        BOOST_LOG_TRIVIAL(error) << "Writing error! Error code: " << ec << " Bytes transferred: " << bytesTransferred;
        stop();
    }
}

void Session::stop()
{
    _socket.close();
    _server->closeSession(shared_from_this());
}
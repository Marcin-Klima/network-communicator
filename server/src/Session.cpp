//
// Created by waxta on 29.12.2021.
//

#include "Session.h"
#include <boost/log/trivial.hpp>
#include <boost/bind/bind.hpp>

#include <string>

Session::Session(Server& server, tcp::socket socket) :
        _server(server),
        _clientSocket(std::move(socket))
{
    BOOST_LOG_TRIVIAL(debug) << "konstruktor";
}

void Session::open()
{
    asyncAwaitForNewMessage(shared_from_this());
}


void Session::asyncAwaitForNewMessage(std::shared_ptr<Session> self)
{
    //boost::bind has the ability to bind function with shared_poniter of T class as *this* pointer
    _clientSocket.async_read_some(boost::asio::buffer(_data, MAX_MESSAGE_LENGTH),
                                  boost::bind(&Session::messageHandler, shared_from_this(), boost::asio::placeholders::error,
                                              boost::asio::placeholders::bytes_transferred));
}

void Session::messageHandler(boost::system::error_code errorCode, size_t messageLength)
{
    if (!errorCode)
    {
        std::string_view dataView(_data, messageLength);
        BOOST_LOG_TRIVIAL(info) << "client says: " << dataView;

        _server.processMessageFromClient(_data);
        asyncAwaitForNewMessage(shared_from_this());
    }
    else if(errorCode == boost::asio::error::eof)
    {
        BOOST_LOG_TRIVIAL(info) << "closing connection";
        _clientSocket.close();
        _server.closeSession(shared_from_this());
        BOOST_LOG_TRIVIAL(debug) << "after server removed session from map";
    }
}

Session::~Session()
{
    BOOST_LOG_TRIVIAL(debug) << "session's dctor";
}

std::shared_ptr<Session> Session::create(Server& server, tcp::socket socket)
{
    return std::shared_ptr<Session>(new Session(server, std::move(socket)));
}


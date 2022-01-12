//
// Created by waxta on 29.12.2021.
//

#include "Session.h"
#include <boost/log/trivial.hpp>
#include <boost/bind/bind.hpp>

#include <string>

Session::Session(tcp::socket socket, size_t sessionId) : _clientSocket(std::move(socket)), _sessionId(sessionId)
{
    asyncAwaitForNewMessage();
}

void Session::asyncAwaitForNewMessage()
{
    _clientSocket.async_read_some(boost::asio::buffer(_data, MAX_MESSAGE_LENGTH),
                                  boost::bind(&Session::messageHandler, this, boost::asio::placeholders::error,
                                              boost::asio::placeholders::bytes_transferred));
}

void Session::messageHandler(boost::system::error_code errorCode, size_t messageLength)
{
    if (!errorCode)
    {
        std::string_view dataView(_data, messageLength);
        BOOST_LOG_TRIVIAL(info) << "client says: " << dataView;

        if (dataView == "/endsession")
        {
            BOOST_LOG_TRIVIAL(info) << "closing connection";
            _clientSocket.close();
            emit sessionClosed(_sessionId);
        } else
        {
            asyncAwaitForNewMessage();
        }
    }
}

Session::~Session()
{
    BOOST_LOG_TRIVIAL(info) << "closing session";
}

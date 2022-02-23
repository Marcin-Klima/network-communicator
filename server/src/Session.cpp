//
// Created by waxta on 29.12.2021.
//

#include "Session.h"
#include <boost/log/trivial.hpp>
#include <boost/bind/bind.hpp>

#include <string>

Session::Session(std::list<std::shared_ptr<Session>>& sessions, tcp::socket socket) :
        _sessionList(sessions),
        _socket(std::move(socket))
{
    BOOST_LOG_TRIVIAL(debug) << "konstruktor";
}

void Session::open()
{
    asyncAwaitForNewMessage();
}


void Session::asyncAwaitForNewMessage()
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
        std::string_view dataView(_data, messageLength);
        BOOST_LOG_TRIVIAL(info) << "client says: " << dataView;

        for (auto otherSession: _sessionList)
        {
            if (otherSession != shared_from_this())
            {
                otherSession->_socket.async_send(boost::asio::buffer(_data, messageLength),
                                                 []([[maybe_unused]]
                boost::system::error_code ec, [[maybe_unused]] std::size_t bytes_transferred) {
                    if(!ec)
                    {
                        BOOST_LOG_TRIVIAL(info) << "OK! bytes transferred: " << bytes_transferred;
                    }
                });
            }
        }

        memset(_data, 0, MAX_MESSAGE_LENGTH);
        asyncAwaitForNewMessage();
    }
    else if (errorCode == boost::asio::error::eof)
    {
        BOOST_LOG_TRIVIAL(debug) << "SOCKET'S EOF";
        _socket.close();
        _sessionList.erase(std::find(_sessionList.begin(), _sessionList.end(), shared_from_this()));
    }
}

Session::~Session()
{
    BOOST_LOG_TRIVIAL(debug) << "session's destructor";
}

std::shared_ptr<Session> Session::create(std::list<std::shared_ptr<Session>>& sessions, tcp::socket socket)
{
    return std::shared_ptr<Session>(new Session(sessions, std::move(socket)));
}

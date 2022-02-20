//
// Created by waxta on 29.12.2021.
//

#pragma once

#include <boost/asio.hpp>
#include "Server.h"

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
    enum
    {
        MAX_MESSAGE_LENGTH = 1024
    };

public:
    static std::shared_ptr<Session> create(Server& server, tcp::socket socket);
    ~Session();
    void open();


private:
    Session(Server& server, tcp::socket socket);
    void asyncAwaitForNewMessage();
    void messageHandler(boost::system::error_code errorCode, size_t messageLength);

    Server& _server;
    tcp::socket _clientSocket;
    char _data[MAX_MESSAGE_LENGTH];
};

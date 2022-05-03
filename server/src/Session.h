//
// Created by waxta on 29.12.2021.
//

#pragma once

#include <boost/asio.hpp>
#include "Server.h"

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
    using SessionsList = std::list<std::shared_ptr<Session>>;
    enum
    {
        MAX_MESSAGE_LENGTH = 5120
    };

public:
    static std::shared_ptr<Session> create(Server* server, tcp::socket socket);
    ~Session();
    void open();
    void dispatchMessage(std::shared_ptr<std::string> message);

private:
    Session(Server* server, tcp::socket socket);
    void awaitMessage();
    void writeHandler(boost::system::error_code ec, size_t bytesTransferred);
    void awaitMessageHandler(boost::system::error_code errorCode, size_t messageLength);
    void stop();

    void startWriting();

    Server* _server;
    tcp::socket _socket;

    char _data[MAX_MESSAGE_LENGTH] = {0};
    std::deque<std::shared_ptr<std::string>> _writeMessageQueue;
};

//
// Created by waxta on 29.12.2021.
//

#pragma once

#include <deque>
#include <boost/asio.hpp>

#include "ServerInterface.h"

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
    enum
    {
        MAX_MESSAGE_LENGTH = 5120
    };

public:
    static std::shared_ptr<Session> create(ServerInterface* serverInterface, tcp::socket socket);
    ~Session();
    void open();
    void dispatchMessage(std::shared_ptr<std::string> message);

private:
    Session(ServerInterface* serverInterface, tcp::socket socket);
    void awaitMessage();
    void writeHandler(boost::system::error_code ec, size_t bytesTransferred);
    void awaitMessageHandler(boost::system::error_code errorCode, size_t messageLength);
    void stop();

    void write();

    ServerInterface* _serverInterface;
    tcp::socket _socket;

    char _data[MAX_MESSAGE_LENGTH] = {0};
    std::deque<std::shared_ptr<std::string>> _writeMessageQueue;
};

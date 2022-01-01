//
// Created by waxta on 29.12.2021.
//

#pragma once

#include <boost/asio.hpp>
#include <QObject>

using boost::asio::ip::tcp;

class Session : public QObject
{
    Q_OBJECT

    enum
    {
        MAX_MESSAGE_LENGTH = 1024
    };

public:
    Session(tcp::socket socket, size_t sessionId);
    ~Session();

signals:
    void sessionClosed(size_t sessionId);

private:
    void asyncAwaitForNewMessage();
    void messageHandler(boost::system::error_code errorCode, size_t messageLength);

    tcp::socket _clientSocket;
    char _data[MAX_MESSAGE_LENGTH];
    const size_t _sessionId;
};

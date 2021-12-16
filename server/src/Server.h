//
// Created by Marcin on 8/10/2021.
//

#pragma once

#include <QObject>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server();
    ~Server();

signals:
    void printMessage(const QString& message);

public slots:
    void receiveInputFromFrontent(const QString& input);

private:
    void threadLoop();
    void halt();
    void acceptNewConnection();

    std::unique_ptr<boost::thread> _thread;
    boost::asio::io_context _io_context;
    tcp::endpoint _endpoint;
    tcp::acceptor _acceptor;
};

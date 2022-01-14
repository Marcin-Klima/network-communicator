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

    friend class Session;

public:
    explicit Server();
    ~Server();

signals:
    void printMessage(const QString& message);
    void serverStarted();
    void serverStopped();

public slots:
    void receiveInputFromFrontend(const QString& input);
    void stopServer();
    void startServer();

private slots:
    void closeSession(Session* session);

private:
    void threadLoop();
    void acceptNewConnection();

    std::map<class Session*, std::shared_ptr<Session>> _sessions;
    std::unique_ptr<boost::thread> _thread;
    boost::asio::io_context _io_context;
    tcp::endpoint _endpoint;
    tcp::acceptor _acceptor;
};

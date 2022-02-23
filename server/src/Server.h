//
// Created by Marcin on 8/10/2021.
//

#pragma once

#include <QObject>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Session;

class Server : public QObject
{
    Q_OBJECT

    friend class Session;

public:
    explicit Server();
    ~Server();
    void processMessageFromClient(std::shared_ptr<Session> sender, const QString& message);

signals:
    void printMessage(const QString& message);
    void serverStarted();
    void serverStopped();
    void clientConnected();
    void clientDisconnected();

public slots:
    void receiveInputFromFrontend(const QString& input);
    void startServer();
    void stopServer();
    void testSlot();

private slots:
    void closeSession(std::shared_ptr<Session> session);

private:
    void threadLoop();
    void acceptNewConnection();

    std::list<std::shared_ptr<Session>> _sessions;
    std::unique_ptr<boost::thread> _thread;
    boost::asio::io_context _ioContext;
    tcp::endpoint _endpoint;
    tcp::acceptor _acceptor;
    bool _running;
};

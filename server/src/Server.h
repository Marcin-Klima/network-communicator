//
// Created by Marcin on 8/10/2021.
//

#pragma once

#include <QObject>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <deque>
#include <set>

using boost::asio::ip::tcp;

class Session;

class Server : public QObject
{
    Q_OBJECT

    friend class Session;

public:
    explicit Server();
    void sendOutMessage(const std::shared_ptr<Session>& sender, const std::string& message);
    void messageSubmittedToNetworkStack(const std::shared_ptr<Session>& sender, std::shared_ptr<std::string> message);

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
    void acceptNewConnection();

    std::set<std::shared_ptr<Session>> _sessions;
    boost::asio::io_context _ioContext;
    tcp::endpoint _endpoint;
    tcp::acceptor _acceptor;
    bool _running;
    std::unique_ptr<boost::thread> _thread;
    std::unordered_map<std::shared_ptr<std::string>, size_t> _messageMap;
    std::mutex _clientQueueMutex;
};

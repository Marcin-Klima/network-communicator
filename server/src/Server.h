//
// Created by Marcin on 8/10/2021.
//

#pragma once

#include <QObject>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <deque>
#include <set>
#include "ServerInterface.h"

using boost::asio::ip::tcp;

class Server : public QObject, public ServerInterface
{
    Q_OBJECT

public:
    explicit Server();

    //ServerInterface implementation
    void notifyMessageSubmittalToNetworkStack(const std::shared_ptr<Session>& sender,
                                              std::shared_ptr<std::string> message) override;
    void deliverMessage(const std::shared_ptr<Session>& sender, std::shared_ptr<std::string> message) override;
    void closeSession(const std::shared_ptr<Session>& session) override;

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

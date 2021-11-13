//
// Created by Marcin on 8/10/2021.
//

#pragma once

#include <QObject>
#include <boost/thread/thread.hpp>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server();
    ~Server();
    void start();

signals:
    void printMessage(const QString& message);

public slots:
    void parseCommand(const QString& command);


private:
    void threadLoop();
    void halt();

    std::unique_ptr<boost::thread> _thread;
};

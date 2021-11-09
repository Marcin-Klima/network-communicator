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

public slots:
    void start();
    void stop(QString& command);

signals:
    void serverCreated();

private:
    void run();

    std::unique_ptr<boost::thread> _thread;
};

//
// Created by waxta on 07.01.2022.
//

#pragma once


#include <QObject>

#include <memory>

#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Backend : public QObject
{
    Q_OBJECT

public:
    Backend();
    ~Backend();
    void run();

signals:

public slots:
    void receiveInputFromFrontend(const QString& string);
    void stopClientSession();

private:
    void threadFunction();

    std::unique_ptr<boost::thread> _mainThread;
    boost::asio::io_context _ioContext;
    tcp::socket _socket;
};


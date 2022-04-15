//
// Created by waxta on 07.01.2022.
//

#include "Backend.h"

#include <boost/log/trivial.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

Backend::Backend() : _socket(_ioContext)
{

}

void Backend::run()
{
    _mainThread = std::make_unique<boost::thread>(&Backend::threadFunction, this);
}

void Backend::threadFunction()
{
    try
    {
        BOOST_LOG_TRIVIAL(info) << "Starting main client thread";

        tcp::resolver resolver(_ioContext);
        boost::asio::connect(_socket, resolver.resolve(boost::asio::ip::host_name(), "6969"));

        waitForMessage();

        _ioContext.run();
    }
    catch (std::exception& exception)
    {
        BOOST_LOG_TRIVIAL(error) << exception.what();
    }

    BOOST_LOG_TRIVIAL(info) << "end of thread";
}

void Backend::receiveInputFromFrontend(const QString& string)
{
    boost::asio::async_write(_socket, boost::asio::buffer(string.toStdString(), string.length()),
                             [this](boost::system::error_code ec,
                                    std::size_t bytesTransferred) {
                                 if (!ec)
                                 {
                                     BOOST_LOG_TRIVIAL(debug) << "sending: " << _buffer;
                                 } else
                                 {
                                     stop();
                                     //todo: signal to frontend
                                 }
                             });
}

Backend::~Backend()
{
    if (_mainThread != nullptr && _mainThread->joinable())
    {
        _mainThread->join();
    }
    BOOST_LOG_TRIVIAL(info) << "backend destructor!";
}

void Backend::stop()
{
    BOOST_LOG_TRIVIAL(debug) << "end work";
    _socket.close();
    _ioContext.stop();
}

void Backend::waitForMessage()
{
    _socket.async_read_some(boost::asio::buffer(_buffer, 1024),
                            boost::bind(&Backend::waitForMessageHandler, this, boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

void Backend::waitForMessageHandler(boost::system::error_code ec, std::size_t messageLength)
{
    if (!ec)
    {
        emit messageReceived(_buffer);
        memset(_buffer, 0, 1024);
        waitForMessage();
    } else
    {
        stop();
        //todo: signal frontend about connection error!
    }
}
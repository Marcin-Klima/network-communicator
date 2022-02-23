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
        resolver.async_resolve(boost::asio::ip::host_name(), "6969",
                                boost::bind(&Backend::resolveHandler, this, boost::asio::placeholders::error,
                                            boost::asio::placeholders::results));

        _ioContext.run();
    }
    catch (std::exception& exception)
    {
        BOOST_LOG_TRIVIAL(error) << exception.what();
    }
}

void Backend::receiveInputFromFrontend(const QString& string)
{
    _socket.async_send(boost::asio::buffer(string.toStdString(), string.length()),
                       [this]([[maybe_unused]] boost::system::error_code ec,
                          [[maybe_unused]] std::size_t bytesTransferred) {
                           BOOST_LOG_TRIVIAL(debug) << "sending: " << _buffer;
                       });
}

Backend::~Backend()
{
    if (_mainThread != nullptr && _mainThread->joinable())
    {
        _mainThread->join();
    }
}

void Backend::stop()
{
    BOOST_LOG_TRIVIAL(debug) << "end work";
    _socket.close();
    _ioContext.stop();
}

void Backend::readMessage()
{
    _socket.async_read_some(boost::asio::buffer(_buffer, 1024),
                            [this](boost::system::error_code ec, [[maybe_unused]] std::size_t messageLength) {
                                if (!ec)
                                {
                                    emit messageReceived(_buffer);
                                    memset(_buffer, 0, 1024);
                                    readMessage();
                                }
                            });
}

void Backend::resolveHandler(boost::system::error_code ec, tcp::resolver::results_type result)
{
    if (!ec)
    {
        boost::asio::async_connect(_socket, result,
                                   [this](const boost::system::error_code& ec,
                                          [[maybe_unused]] const boost::asio::ip::tcp::endpoint& endpoint) {
                                       if (!ec)
                                       {
                                           readMessage();
                                       }
                                   });
    }
}

//
// Created by waxta on 07.01.2022.
//

#include "Backend.h"

#include <boost/log/trivial.hpp>

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
    }
    catch(std::exception& exception)
    {
        BOOST_LOG_TRIVIAL(error) << exception.what();
    }
}

void Backend::receiveInputFromFrontend(const QString& string)
{
    boost::asio::write(_socket, boost::asio::buffer(string.toStdString()));
}

Backend::~Backend()
{
    if(_mainThread != nullptr && _mainThread->joinable())
    {
        _mainThread->join();
    }
}

void Backend::stopClientSession()
{
    boost::asio::write(_socket, boost::asio::buffer("/endsession"));
}

//
// Created by Marcin on 8/10/2021.
//

#pragma once

#include <boost/asio.hpp>

#include <string>

using boost::asio::ip::tcp;

class Server
{
public:
    Server();
    void Run();

private:
    void ConnectionAccept(boost::system::error_code errorCode, tcp::socket socket);

    void AcceptNewConnections(tcp::acceptor &acceptor);

    std::string makeDaytimeString();
};

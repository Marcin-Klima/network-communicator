//
// Created by Marcin on 8/5/2021.
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

#include "Frontend.h"

using boost::asio::ip::tcp;

int main(int argc, char** argv)
{
    Frontend frontend;
    frontend.run(argc, argv);

    return 0;
//    try
//    {
//        BOOST_LOG_TRIVIAL(info) << "Starting client";
//        boost::asio::io_context io_context;
//        tcp::resolver resolver(io_context);
//        tcp::socket socket(io_context);
//        boost::asio::connect(socket, resolver.resolve(boost::asio::ip::host_name(), "6969"));
//
//        std::string message;
//        while(message != "/close")
//        {
//            std::getline(std::cin, message);
//            boost::asio::write(socket, boost::asio::buffer(message));
//        }
//    }
//    catch(std::exception& exception)
//    {
//        BOOST_LOG_TRIVIAL(error) << exception.what();
//    }
//
//	return 0;
}
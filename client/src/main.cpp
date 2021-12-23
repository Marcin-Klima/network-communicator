//
// Created by Marcin on 8/5/2021.
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

using boost::asio::ip::tcp;

int main()
{
    try
    {
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::socket socket(io_context);
        boost::asio::connect(socket, resolver.resolve("DESKTOP-SKA4OVV", "6969"));
    }
    catch(std::exception& exception)
    {
        BOOST_LOG_TRIVIAL(error) << exception.what();
    }

	return 0;
}
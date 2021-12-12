//
// Created by Marcin on 8/5/2021.
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main()
{
    try
    {
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::socket socket(io_context);
        boost::asio::connect(socket, resolver.resolve("waxta-laptop", "6969"));
    }
    catch(std::exception& exception)
    {
        std::cout << "FAIL" << std::endl;
        std::cout << exception.what();
    }

	return 0;
}
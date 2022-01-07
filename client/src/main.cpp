//
// Created by Marcin on 8/5/2021.
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

#include "Frontend.h"
#include "Backend.h"

using boost::asio::ip::tcp;

int main(int argc, char** argv)
{
    Backend backend;
    Frontend frontend(argc, argv, backend);
    frontend.run();

    BOOST_LOG_TRIVIAL(info) << "youre fucked XD";
    return 0;
}
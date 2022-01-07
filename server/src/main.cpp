#include <boost/log/trivial.hpp>

#include "Server.h"
#include "Frontend.h"

int main(int argc, char** argv)
{
    BOOST_LOG_TRIVIAL(info) << "Running application";

    Server server;
    Frontend frontend;
    frontend.run(argc, argv, server);

    return 0;
}
#include <spdlog/spdlog.h>

#include "Server.h"
#include "Frontend.h"

int main(int argc, char** argv)
{
    spdlog::info("Running server application");

    Server server;
    Frontend frontend;
    frontend.run(argc, argv, server);

    return 0;
}
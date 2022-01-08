//
// Created by Marcin on 8/5/2021.
//

#include "Frontend.h"
#include "Backend.h"

int main(int argc, char** argv)
{
    Backend backend;
    Frontend frontend;

    backend.run(); //forks new thread
    frontend.run(argc, argv, backend);

    return 0;
}
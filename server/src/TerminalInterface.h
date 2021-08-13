//
// Created by Marcin on 8/10/2021.
//

#pragma once

#include <boost/thread/thread.hpp>
#include <boost/function.hpp>

class TerminalInterface
{
public:
    TerminalInterface();

    ~TerminalInterface();

    void operator()();

    void Stop();

private:
    boost::thread _thread;

    bool running;

    const std::map<std::string, boost::function<void()>> commandMap = {
            {"exit", boost::bind(&TerminalInterface::Stop, this)}
    };
};

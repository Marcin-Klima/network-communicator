//
// Created by Marcin on 8/18/2021.
//

#pragma once


#include "TerminalInterface.h"

class TerminalOutput
{
public:
    TerminalOutput(TerminalInterface &terminalInterface);
    void Print(const std::string &outputString);

private:
    TerminalInterface &terminalInterface;
};

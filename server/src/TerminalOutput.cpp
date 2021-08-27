//
// Created by Marcin on 8/18/2021.
//

#include "TerminalOutput.h"


TerminalOutput::TerminalOutput(TerminalInterface &terminalInterface) : terminalInterface(terminalInterface)
{

}

void TerminalOutput::Print(const std::string &outputString)
{
    terminalInterface.PrintMessage(outputString);
}

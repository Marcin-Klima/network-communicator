//
// Created by Marcin on 8/10/2021.
//

#include <iostream>
#include "TerminalInterface.h"
#include "TerminalInterfaceServerMediator.h"
#include <boost/function.hpp>
#include <conio.h>
#include <windows.h> //include only under windows! todo: create macrodefinition

namespace
{
    constexpr auto COMMAND_PROMPT = "server>>>";
}

TerminalInterface::TerminalInterface() :
        _running(false)
{
}

TerminalInterface::~TerminalInterface()
{
    _thread->join();
}

void TerminalInterface::ThreadLoop()
{
    char character;
    INPUT_RECORD inputBuffer[128];
    HANDLE stdinHandle;
    DWORD dataRead;

    stdinHandle = GetStdHandle(STD_INPUT_HANDLE);

    while (_running) {
        terminalMutex.lock();
        std::cout << COMMAND_PROMPT << _currentCommand;
        terminalMutex.unlock();

        char inputCharacter = 0;
        while (inputCharacter != '\r') {
            ReadConsoleInput(stdinHandle, inputBuffer, 128, &dataRead);
            for (int i = 0; i < dataRead; ++i) {
                if (inputBuffer[i].EventType == KEY_EVENT) {
                    if (inputBuffer[i].Event.KeyEvent.bKeyDown) {
                        inputCharacter = inputBuffer[i].Event.KeyEvent.uChar.AsciiChar;
                        if (inputCharacter != '\r') {
                            if (inputCharacter == '\b') {

                            }
                            std::cout << inputCharacter;
                        }
                    }
                }
            }
        }

        if (_currentCommand == "exit") {
            Stop();
        } else {
            std::cout << _currentCommand << '\n';
        }

        _currentCommand.clear();
    }
}

void TerminalInterface::Stop()
{
    _mediator->HaltServer();
    _running = false;
}

void TerminalInterface::PrintMessage(const std::string& message)
{
    boost::lock_guard lock(terminalMutex);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    std::string emptyLine("\r" + std::string(columns, ' ') + message);
    std::cout << emptyLine << '\n';

    std::cout << COMMAND_PROMPT << _currentCommand;
}

void TerminalInterface::Run()
{
    _running = true;
    _thread = std::unique_ptr<boost::thread>(new boost::thread(&TerminalInterface::ThreadLoop, this));
}

void TerminalInterface::SetMediator(TerminalInterfaceServerMediator* terminalInterfaceServerMediator)
{
    _mediator = terminalInterfaceServerMediator;
}
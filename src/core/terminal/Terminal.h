#ifndef TERMINAL_H
#define TERMINAL_H

#include "dpp/dpp.h"

class Terminal
{
    public:
        Terminal();
    private:

    void showMenuHeader(const std::string& title);
    void showMenuContent(const short& contentID);
    int handleInput();

};

#endif // TERMINAL_H

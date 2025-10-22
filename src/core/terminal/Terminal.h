#ifndef TERMINAL_H
#define TERMINAL_H

#include "dpp/dpp.h"

class Terminal
{
    public:
        Terminal();
        int run();
    private:

     enum class Menu {
        Main = 0,
        Config,
        SlashCommandsMain,
        SlashCommandsRegister,
        SlashCommandsDelete,
        GuildList,
        Exit
    };

    void showMenuHeader(const std::string& title);
    void showMenuContent(const Menu& contentID);
    int handleInput();

};

#endif // TERMINAL_H

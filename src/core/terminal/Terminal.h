#ifndef TERMINAL_H
#define TERMINAL_H


class Terminal
{
    public:
        Terminal();
        enum class PilihanMenu {
            START_BOT,
            SLASHCOMMAND_CONFIG,
            EXIT
        };

        PilihanMenu run();

    private:


};

#endif // TERMINAL_H

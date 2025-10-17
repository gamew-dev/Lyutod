#ifndef TERMINAL_H
#define TERMINAL_H


class Terminal
{
    public:
        Terminal();
        int run();

    private:

    void showMenuHeader(const std::string& title);
    void showMenuContent(const short& contentID);
    void handleInput();

};

#endif // TERMINAL_H

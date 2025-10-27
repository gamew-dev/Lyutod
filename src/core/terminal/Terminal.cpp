#include "Terminal.h"

using namespace std;

void Terminal::showMenuHeader(const std::string& title) {
    cout << "\033[2J";

    cout << "*** " + title + " ***" << endl;
}

void Terminal::showMenuContent(const Menu& contentID) {
    switch (contentID) {

    case Menu::Main:
        cout << "1. Start\n"
             << "2. Slashcommand\n"
             << "3. Exit\n";
    break;

    case Menu::SlashCommandsMain:
        showMenuHeader("Slash command setting");
        cout << "1. Register slash command\n"
             << "2. Remove slash command\n"
             << "3. Return";

    break;

    //case Menu::
        //cout <<
    //break;

    /*
    case Menu::
        cout <<
    break;
    */

    }
}

int Terminal::handleInput() {
    int key;
    cout << "input: ";
    cin >> key;
    return key;
}

int Terminal::run() {

    //using namespace Terminal;
    Menu menuNow = Menu::Main;


    showMenuHeader("Lyudya startup TUI");
    showMenuContent(menuNow);

    while (true) {

    }

}

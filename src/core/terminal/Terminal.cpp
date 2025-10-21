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



    }
}

void Terminal::handleInput() {
    int key;
    cout << "input: ";
    cin >> key;
    return key;
}

int Terminal::run() {

    using namespace Terminal;
    Menu menuNow = Menu::Main;


    showMenuHeader("Lyudya startup TUI");
    showMenuContent(menuNow);


}

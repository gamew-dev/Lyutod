#include "Terminal.h"

using namespace std;

void Terminal::showMenuHeader(const std::string& title) {
    cout << "\033[2J";

    cout << "*** " + title + " ***" << endl;
}

void Terminal::showMenuContent(const short& contentID) {
    switch (contentID) {

    case 1:
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

#include <iostream>
using namespace std;

void clearScreen() {
    cout << "\033[2J\033[H";
}

void banner(){
    cout << "+=======================================================================+" << endl;
    cout << "|                                                                       |" << endl;
    cout << "|      _    _                         _   ____            _             |" << endl;
    cout << "|     / \\  | |__  _   _ ___ ___  __ _| | |  _ \\ ___  __ _| |_ __ ___    |" << endl;
    cout << "|    / _ \\ | '_ \\| | | / __/ __|/ _` | | | |_) / _ \\/ _` | | '_ ` _ \\   |" << endl;
    cout << "|   / ___ \\| |_) | |_| \\__ \\__ \\ (_| | | |  _ <  __/ (_| | | | | | | |  |" << endl;
    cout << "|  /_/   \\_\\_.__/ \\__, |___/___/\\__,_|_| |_| \\_\\___|\\__,_|_|_| |_| |_|  |" << endl;
    cout << "|                 |___/                                                 |" << endl;
    cout << "|                                                                       |" << endl;
    cout << "+=======================================================================+" << endl;
}

void pressEnter() {
    cout << "Press ENTER to continue...";
    cin.ignore();
    cin.get();
}

void menu(){
    cout << "+========================================================================+" << endl;
    cout << "|                       1. Pride                                        |" << endl;
    cout << "|                       2. Greed                                        |" << endl;
    cout << "|                       3. Wrath                                        |" << endl;
    cout << "|                       4. Sloth                                        |" << endl;
    cout << "|                       5. Gluttony                                     |" << endl;
    cout << "|                       6. Envy                                         |" << endl;
    cout << "|                       7. Lust                                         |" << endl;
    cout << "|                       8. EXIT                                         |" << endl;
    cout << "+========================================================================+" << endl;

}
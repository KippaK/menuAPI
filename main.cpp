#include <iostream>
#include <conio.h>
#include "menuapi.h"

using namespace std;


int main() {
    Menu menu("", {"Home", "Previous", "Next", "Exit"});
    menu.print();
    char input;
    int selectedOption;
    for (;;) {
        input = _getch();
        if (input == 's') {
            menu.moveDown();
        }
        if (input == 'w') {
            menu.moveUp();
        }
        if (input == ' ') {
            selectedOption = menu.exit();
            break;
        }
    }
    cout << "Selected option: " << menu.getOption(selectedOption) << endl;
}
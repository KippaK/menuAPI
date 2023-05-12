#include <iostream>
#include <conio.h>
#include "menuapi.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;


int main() {
    Menu menu("", {"Home", "Previous", "Next", "Exit"});
    menu.print();
    int input;
    int selectedOption;
    for (;;) {
        input = getch();
        if (input == KEY_DOWN) {
            menu.moveDown();
        }
        if (input == KEY_UP) {
            menu.moveUp();
        }
        if (input == ' ') {
            selectedOption = menu.exit();
            break;
        }
    }
    cout << "Selected option: " << menu.getOption(selectedOption) << endl;
}
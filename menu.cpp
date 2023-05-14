#include <conio.h>
#include <iostream>
#include <string>
#include <vector>

#include "menu.h"

using   std::cin,
        std::cout,
        std::endl;


Menu::Menu(string aHeader, vector<string> aOptions) {
    header = aHeader;
    options = aOptions;
    value = 0;
}

Menu::Menu(string aHeader, vector<string> aOptions, char up, char down, char enter) {
    header = aHeader;
    options = aOptions;
    nav.up = up;
    nav.down = down;
    nav.enter = enter;
    value = 0;
}

Menu::~Menu() {}

void Menu::start(){
    value = 0;
    char input;
    for (;;) {
        input = getch();
        if (input == nav.down) {
            moveDown();
        }
        if (input == nav.up) {
            moveUp();
        }
        if (input == nav.enter) {
            value = getActivePosition();
            break;
        }
    }
    resetActivePosition();
}

int Menu::getValue() {
    return value;
}


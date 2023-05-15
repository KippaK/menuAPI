#include <iostream>
#include <conio.h>
#include "menuapi.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 10

#define STRECH_X false
#define CENTER_X        true
#define CENTER_Y        true

using std::cin;
using std::cout;
using std::endl;


int main() {
    const Flags GLOBAL_FLAGS {STRECH_X, CENTER_X, CENTER_Y}; 
    MenuAPI* menu = new MenuAPI(
        "", 
        {
            "Home", 
            "Previous", 
            "Next", 
            "Exit"
        },
        {
            KEY_UP, 
            KEY_DOWN, 
            ' '
        },
        GLOBAL_FLAGS
    );
    menu->start();
    cout << "Selected option: " << menu->getValueName() << endl;
}
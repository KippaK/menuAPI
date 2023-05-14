#include <iostream>
#include <conio.h>
#include "menuapi.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;


int main() {
    MenuAPI menu("", {"Home", "Previous", "Next", "Exit"}, KEY_UP, KEY_DOWN, KEY_RIGHT);
    menu.start();
    cout << "Selected option: " << menu.getValue() << endl;
}
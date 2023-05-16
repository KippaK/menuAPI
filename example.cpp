#include <iostream>
#include <conio.h>
#include <cstdlib>
#include "menuapi.h"

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
const HWND consoleWindow = GetConsoleWindow();
#elif defined(__linux__)
#include <sys/ioctl.h>
#endif

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 10

#define STRECH_X    false
#define STRECH_Y    false
#define CENTER_X    true
#define CENTER_Y    true


using std::cin;
using std::cout;
using std::endl;

void closeWindow() {
    #if defined(_WIN32)
        if (consoleWindow != NULL) {
            PostMessage(consoleWindow, WM_CLOSE, 0, 0);
        }
    #elif defined(__linux__)
        std::system("killall -9 $(basename $SHELL)");
    #endif
}

int main() {
    const Flags GLOBAL_FLAGS {STRECH_X, STRECH_Y, CENTER_X, CENTER_Y};
    MenuAPI* menu = new MenuAPI(
        "", 
        {
            "Home", 
            "Previous", 
            "Next", 
            "Exit"
        },
        {
            'w', 
            's', 
            ' '
        },
        GLOBAL_FLAGS
    );
    menu->start();
    cout << "Selected option: " << menu->getValueName() << endl;
    cout << "Index of selected option: " << menu->getValueIdx() << endl;
    cout << "Press any key to exit";
    _getch();
    closeWindow();
}
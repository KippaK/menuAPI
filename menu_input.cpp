#include "menu.h"
#include <iostream>
#include <conio.h>
#include <cmath>
#include <algorithm>

using   std::cin,
        std::cout,
        std::endl,
        std::min,
        std::floor,
        std::ceil;

bool Menu::Input::validKeyPress(char c) const
{
    if ((int) c >= 97 && (int) c <= 122) {
        return true;
    }
    return false;
}

Menu::Input::Input()
{
    Input(
        "",
        {
            false,
            false,
            false,
            false
        }
    );
}

Menu::Input::Input(string aHeader, Flags aFlags)
{
    Input(aHeader, 24, aFlags);
}

Menu::Input::Input(string aHeader, uint16_t aMaxStrLen, Flags aFlags)
{
}

void Menu::Input::setHeader(string aHeader)
{
    header = aHeader;
}

string Menu::Input::getHeader() const
{
    return header;
}

/*
BOX CHARACTERS
│   179
┐   191
└   192
─   196
┘   217
┌   218
*/

void Menu::Input::print(string input) const
{
    system("CLS");
    // TODO
}

void Menu::Input::start()
{
    setCursorVisibility(false);
    char c;
    string input;
    print(input);
    for (;;) {
        print(input);
        c = getch();
        if (input.length() > 0 && (int) c == 8) {
            input.pop_back();
        }
        else if (validKeyPress(c)) {
            input.push_back(c);
        }
        else if ((int) c == 13) {
            break;
        }
        else if ((int) c == 27) {
            break;
        }
    }
    str = input;
    system("CLS");
    setCursorVisibility(true);
}

string Menu::Input::getString() const
{
    return str;
}

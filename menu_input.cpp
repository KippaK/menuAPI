#include "menu.h"
#include <iostream>
#include <conio.h>
#include <cmath>
#include <algorithm>
#include <iomanip>

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
    header = aHeader;
    maxStrLen = aMaxStrLen;
    flags = aFlags;
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
    // Flags: stretchY, stretchX
    // Print header

    int width, heigth;
    int ILSpace, IRSpace;
    int ITSpace = 0, IBSpace = 0;
    int HLSpace, HRSpace;
    int remainingSpace;
    int menuWidth = maxStrLen;

    // GENERAL CALCULATIONS
    getTerminalSize(width, heigth);
    int centerX = 0, centerY = 0;
    if (flags.centerX) {
        centerX = ceil(width / 2) - floor(maxStrLen / 2);
    }
    if (flags.centerY) {
        centerY = (heigth - 3) / 2;
    }
    if (flags.stretchX) {
        menuWidth = width - 2;
        centerX = 0;
    }
    if (flags.stretchY) {
        ITSpace = (heigth - 3) / 2;
        IBSpace = ITSpace;
        if (heigth % 2 == 0) {
            ITSpace++;
        }
    }


    // TOP CALCULATIONS
    HLSpace = (menuWidth - header.length()) / 2;
    HRSpace = HLSpace;
    if ((menuWidth - header.length()) % 2 == 1) {
        HRSpace++;
    }

    // MIDDLE CALCULATIONS
    if (input.length() > menuWidth) {
        input = input.substr(input.length() - menuWidth, string::npos);
        remainingSpace = 0;    
    }
    else {
        remainingSpace = menuWidth - input.length();
    }

    ILSpace = remainingSpace / 2;
    IRSpace = ILSpace;
    if (remainingSpace % 2 == 1) {
        IRSpace++;
    }

    for (int i = 0; i < centerY; i++) { cout << '\n'; }
    // HEADER PRINT
    cout.width(centerX);
    cout    << char(218) 
            << string(HLSpace, char(196))
            << header
            << string(HRSpace, char(196))
            << char(191) << '\n';

    // TOP FILL
    for (int i = 0; i < ITSpace; i++) {
        cout.width(centerX);
        cout << char(179) << string(menuWidth, ' ') << char(179) << '\n';    
    }

    // INPUT LINE
    cout.width(centerX);
    cout    << char(179)
            << string(ILSpace, ' ') << input << string(IRSpace, ' ')
            << char(179) << '\n';

    // BOTTOM FILL
    for (int i = 0; i < IBSpace; i++) {
        cout.width(centerX);
        cout << char(179) << string(menuWidth, ' ') << char(179) << '\n';    
    }

    // BOTTOM PRINT
    cout.width(centerX);
    cout << char(192) << string(menuWidth, char(196)) << char(217);
}

void Menu::Input::start()
{
    setCursorVisibility(false);
    char c;
    string input;
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

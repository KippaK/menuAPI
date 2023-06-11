#include "menu.h"
#include <iostream>
#include <conio.h>
#include <cmath>

using   std::cin,
        std::cout,
        std::endl,
        std::floor,
        std::ceil;
        

Menu::Select::Select()
{
    Select("", {}, {'w', 's', ' '}, {false, false, false, false});
}

Menu::Select::Select(string aHeader, vector<string> aOptions, Nav aNav)
{
    Select(aHeader, aOptions, aNav, {false, false, false, false});
}

Menu::Select::Select(string aHeader, vector<string> aOptions, Nav aNav, Flags aFlags)
{
    value = -1;
    header = aHeader;
    options = aOptions;
    activePosition = 0;
    maxOptionLength = maxLength(aOptions, header.length());
    nav = aNav;
    flags = aFlags;
}

Menu::Select::~Select()
{}

void Menu::Select::setHeader(string aHeader)
{
    header = aHeader;
}

string Menu::Select::getHeader() const
{
    return header;
}

void Menu::Select::setOptions(vector<string> aOptions)
{
    options = aOptions;
    maxOptionLength = maxLength(aOptions, header.length());
}

vector<string> Menu::Select::getOptions() const
{
    return options;
}

string Menu::Select::getOption(int aIdx) const
{
    return options[aIdx];
}

void Menu::Select::setActivePosition(int aIdx)
{
    activePosition = aIdx;
}

int Menu::Select::getActivePosition() const
{
    return activePosition;
}

void Menu::Select::addOption(string aOption)
{
    if (aOption.length() > maxOptionLength) {
        maxOptionLength = aOption.length();
    }
    options.push_back(aOption);
}

void Menu::Select::addOption(string aOption, int aIdx)
{
    if (aOption.length() > maxOptionLength) {
        maxOptionLength = aOption.length();
    }
    options.insert(options.begin() + aIdx, aOption);
}

void Menu::Select::removeOption(int aIdx)
{
    if (maxOptionLength = options[aIdx].length()) {
        options.erase(options.begin() + aIdx);
        maxOptionLength = maxLength(options, header.length());
        return;
    }
    options.erase(options.begin() + aIdx);
}

void Menu::Select::removeOption(string aOption)
{
    for (int i = 0; i < options.size(); i++) {
        if (options[i] == aOption) {
            removeOption(i);
            return;
        }
    }
}

void Menu::Select::resetActivePosition()
{
    activePosition = 0;
}

void Menu::Select::moveDown()
{
    activePosition++;
    if (activePosition >= options.size()) {
        activePosition = 0;
    }
    print();
}

void Menu::Select::moveUp()
{
    activePosition--;
    if (activePosition < 0) {
        activePosition = options.size() - 1;
    }
    print();
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

void Menu::Select::print() const
{
    system("CLS");
    int menuWidth = maxOptionLength + 4;
    int paddingX = 0, paddingY = 0;
    int fillTop = 0, fillBottom = 0; 
    int width = 0, height = 0;
    getTerminalSize(width, height);
    if (flags.stretchX) {
        menuWidth = width - 2;
    }
    if (flags.centerX) {
        paddingX = ceil(width / 2) - floor(menuWidth / 2);
    }
    if (flags.centerY) {
        paddingY = ceil(height / 2) - floor((options.size() + 2) / 2);
    }
    if (flags.stretchY) {
        fillTop = floor((height - 2 - options.size()) / 2);
        fillBottom = ceil((height - 2 - options.size()) / 2);
    }


    for (int i = 0; i < paddingY; i++) {
        cout << "\n";
    }

    string line(menuWidth, char(196));
    
    string cHeader = header;
    for (;;) {
        if (cHeader.length() == menuWidth) { break; }
        cHeader.insert(cHeader.end(), char(196));
        if (cHeader.length() == menuWidth) { break; }
        cHeader.insert(cHeader.begin(), char(196));
    }
    cout.width(paddingX);
        
    cout << char(218) << cHeader << char(191) << endl;

    for (int i = 0; i < fillTop; i++) {
        printLine("", menuWidth, false, paddingX);
    }
    for (int i = 0; i < options.size(); i++) {
        printLine(options[i], menuWidth, (i == activePosition), paddingX);
    }
    for (int i = 0; i < fillBottom; i++) {
        printLine("", menuWidth, false, paddingX);
    }
    cout.width(paddingX);
    cout << char(192) << line << char(217);
}

int Menu::Select::maxLength(const vector<string> &strs, int startValue) const
{
    int max = startValue;
    for (int i = 0; i < strs.size(); i++) {
        if (strs[i].length() > max) {
            max = strs[i].length();
        }
    }
    return max;
}

void Menu::Select::printLine(string content, int width, bool active, int fill) const
{
    if (active) {
        content.insert(content.begin(), '>');
        content.insert(content.end(), '<');
    }
    for (;;) {
        if (content.length() == width) { break; }
        content.insert(content.end(), (active) ? char(196) : ' ');
        if (content.length() == width) { break; }
        content.insert(content.begin(), (active) ? char(196) : ' ');
    }
    cout.width(fill);
    cout << char(179) << content << char(179) << endl;
}

void Menu::Select::start()
{
    setCursorVisibility(false);
    value = -1;
    char input;
    print();
    for (;;) {
        input = _getch();
        if (input == nav.down) { moveDown(); }
        else if (input == nav.up) { moveUp(); }
        else if (input == nav.enter) {
            value = activePosition;
            break;
        }
    }
    system("CLS");
    setCursorVisibility(true);
}

int Menu::Select::getValueIdx()
{
    return value;
}

string Menu::Select::getValueName()
{
    if (value < 0) {return "ERROR: option wasn't selected\n"; }
    return options[value];
}

void Menu::Select::setValue(int aValue)
{
    value = aValue;
}
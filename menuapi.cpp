#include "menuapi.h"
#include <iostream>
#include <conio.h>
#include <cmath>
#include <windows.h>

using   std::cin,
        std::cout,
        std::endl,
        std::floor,
        std::ceil;
        
#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#elif defined(__linux__)
#include <sys/ioctl.h>
#endif // Windows/Linux

void get_terminal_size(int& width, int& height) {
    #if defined(_WIN32)
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        width = (int)(csbi.srWindow.Right-csbi.srWindow.Left+1);
        height = (int)(csbi.srWindow.Bottom-csbi.srWindow.Top+1);
    #elif defined(__linux__)
        struct winsize w;
        ioctl(fileno(stdout), TIOCGWINSZ, &w);
        width = (int)(w.ws_col);
        height = (int)(w.ws_row);
#endif // Windows/Linux
}

void ShowConsoleCursor(bool showFlag) {
    #if defined(_WIN32)
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO     cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = showFlag;
        SetConsoleCursorInfo(out, &cursorInfo);
    #elif defined(__linux__)
    // TODO
#endif
}

MenuAPI::MenuAPI() {
    MenuAPI("", {}, {'w', 's', ' '}, {false, false, false, false});
}

MenuAPI::MenuAPI(string aHeader, vector<string> aOptions, Nav aNav, Flags aFlags) {
    int width = 0, height = 0;
    header = aHeader;
    options = aOptions;
    activePosition = 0;
    maxOptionLength = maxLength(aOptions, header.length());
    nav.up = aNav.up;
    nav.down = aNav.down;
    nav.enter = aNav.enter;
    flags.stretchX = aFlags.stretchX;
    flags.stretchY = aFlags.stretchY;
    flags.centerX = aFlags.centerX;
    flags.centerY = aFlags.centerY;
}

MenuAPI::~MenuAPI() {}

void MenuAPI::setHeader(string aHeader) {
    header = aHeader;
}

string MenuAPI::getHeader() const {
    return header;
}

void MenuAPI::setOptions(vector<string> aOptions) {
    options = aOptions;
    maxOptionLength = maxLength(aOptions, header.length());
}

vector<string> MenuAPI::getOptions() const {
    return options;
}

string MenuAPI::getOption(int aIdx) const {
    return options[aIdx];
}

void MenuAPI::setActivePosition(int aIdx) {
    activePosition = aIdx;
}

int MenuAPI::getActivePosition() const {
    return activePosition;
}

void MenuAPI::addOption(string aOption) {
    if (aOption.length() > maxOptionLength) {
        maxOptionLength = aOption.length();
    }
    options.push_back(aOption);
}

void MenuAPI::addOption(string aOption, int aIdx) {
    if (aOption.length() > maxOptionLength) {
        maxOptionLength = aOption.length();
    }
    options.insert(options.begin() + aIdx, aOption);
}

void MenuAPI::removeOption(int aIdx) {
    if (maxOptionLength = options[aIdx].length()) {
        options.erase(options.begin() + aIdx);
        maxOptionLength = maxLength(options, header.length());
        return;
    }
    options.erase(options.begin() + aIdx);
}

void MenuAPI::removeOption(string aOption) {
    for (int i = 0; i < options.size(); i++) {
        if (options[i] == aOption) {
            removeOption(i);
            return;
        }
    }
}

void MenuAPI::resetActivePosition() {
    activePosition = 0;
}

void MenuAPI::moveDown() {
    activePosition++;
    if (activePosition >= options.size()) {
        activePosition = 0;
    }
    print();
}

void MenuAPI::moveUp() {
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

void MenuAPI::print() {
    system("CLS");
    int menuWidth = maxOptionLength + 4;
    int paddingX = 0, paddingY = 0;
    int fillTop = 0, fillBottom = 0; 
    int width = 0, height = 0;
    get_terminal_size(width, height);
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

int MenuAPI::maxLength(const vector<string> &strs, int startValue) {
    int max = startValue;
    for (int i = 0; i < strs.size(); i++) {
        if (strs[i].length() > max) {
            max = strs[i].length();
        }
    }
    return max;
}

void MenuAPI::printLine(string content, int width, bool active, int fill) {
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

void MenuAPI::start(){
    ShowConsoleCursor(false);
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
    ShowConsoleCursor(true);
}

int MenuAPI::getValueIdx() {
    return value;
}

string MenuAPI::getValueName() {
    return options[value];
}

void MenuAPI::setValue(int aValue) {
    value = aValue;
}
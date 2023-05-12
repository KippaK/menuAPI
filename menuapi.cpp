#include "menuapi.h"
#include <iostream>

using   std::cin,
        std::cout,
        std::endl;
        


int maxLength(const vector<string> &strs, int startValue) {
    int max = startValue;
    for (int i = 0; i < strs.size(); i++) {
        if (strs[i].length() > max) {
            max = strs[i].length();
        }
    }
    return max;
}

void printLine(string content, int width, bool active) {
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
    cout << char(179) << content << char(179) << endl;
}

Menu::Menu() {
    activePosition = 0;
    maxOptionLength = 0;
}

Menu::Menu(string aHeader) {
    header = aHeader;
    activePosition = 0;
    maxOptionLength = 0;
}

Menu::Menu(string aHeader, vector<string> aOptions) {
    header = aHeader;
    options = aOptions;
    activePosition = 0;
    maxOptionLength = maxLength(aOptions, header.length());
}

Menu::~Menu() {}

void Menu::setHeader(string aHeader) {
    header = aHeader;
}

string Menu::getHeader() const {
    return header;
}

void Menu::setOptions(vector<string> aOptions) {
    options = aOptions;
    maxOptionLength = maxLength(aOptions, header.length());
}

vector<string> Menu::getOptions() const {
    return options;
}

string Menu::getOption(int aIdx) const {
    return options[aIdx];
}

void Menu::setActivePosition(int aIdx) {
    activePosition = aIdx;
}

int Menu::getActivePosition() const {
    return activePosition;
}

void Menu::addOption(string aOption) {
    if (aOption.length() > maxOptionLength) {
        maxOptionLength = aOption.length();
    }
    options.push_back(aOption);
}

void Menu::addOption(string aOption, int aIdx) {
    if (aOption.length() > maxOptionLength) {
        maxOptionLength = aOption.length();
    }
    options.insert(options.begin() + aIdx, aOption);
}

void Menu::removeOption(int aIdx) {
    if (maxOptionLength = options[aIdx].length()) {
        options.erase(options.begin() + aIdx);
        maxOptionLength = maxLength(options, header.length());
        return;
    }
    options.erase(options.begin() + aIdx);
}

void Menu::removeOption(string aOption) {
    for (int i = 0; i < options.size(); i++) {
        if (options[i] == aOption) {
            removeOption(i);
            return;
        }
    }
}

void Menu::resetActivePosition() {
    activePosition = 0;
}

void Menu::moveDown() {
    activePosition++;
    if (activePosition >= options.size()) {
        activePosition = 0;
    }
    print();
}

void Menu::moveUp() {
    activePosition--;
    if (activePosition < 0) {
        activePosition = options.size() - 1;
    }
    print();
}

int Menu::exit() {
    return activePosition;
}

void Menu::print() {
    int menuWidth = maxOptionLength + 4;
    system("CLS");

    string line(menuWidth, char(196));
    
    string cHeader = header;
    for (;;) {
        if (cHeader.length() == menuWidth) { break; }
        cHeader.insert(cHeader.end(), char(196));
        if (cHeader.length() == menuWidth) { break; }
        cHeader.insert(cHeader.begin(), char(196));
    }
    cout << char(218) << cHeader << char(191) << endl;

    for (int i = 0; i < options.size(); i++) {
        printLine(options[i], menuWidth, (i == activePosition));
    }
    cout << char(192) << line << char(217) << endl;
}
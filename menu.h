#include "terminal_operations.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace Menu
{
struct Nav {
    char up;
    char down;
    char enter;
};

struct Flags {
    bool stretchX;
    bool stretchY;
    bool centerX;
    bool centerY;
};

class Select : public TerminalOperations
{
public:
    Select();
    Select(    
        string aHeader,
        vector<string> aOptions,
        Nav aNav
    );
    Select(
        string aHeader,
        vector<string> aOptions, 
        Nav aNav,
        Flags Flags
    );
    ~Select();

    void setHeader(string aHeader);
    string getHeader() const;
    void setOptions(vector<string> aOptions);
    vector<string> getOptions() const;
    string getOption(int aIdx) const;
    void setActivePosition(int aIdx);
    int getActivePosition() const;


    void addOption(string aOption);
    void addOption(string aOption, int aIdx);

    void removeOption(int aIdx);
    void removeOption(string aOption);

    void resetActivePosition();

    void moveDown();
    void moveUp();
    void print() const;

    int maxLength(const vector<string> &strs, int startValue) const;
    void printLine(string content, int width, bool active, int fill) const;

    void start();
    int getValueIdx();
    string getValueName();
    void setValue(int aValue);

private:
    string header;
    vector<string> options;
    int activePosition;
    int maxOptionLength;
    int value;
    Nav nav;
    Flags flags;
};

class Input : public TerminalOperations
{
private:
    bool validKeyPress(char c) const;
    void printCharXtimes(char c, uint16_t count) const;
    void printFillLine(int count, int menuWidth) const;
public:
    Input();
    Input(string aHeader, Flags aFlags);
    Input(string aHeader, uint16_t aMaxStrLen, Flags aFlags);

    void setHeader(string aHeader);
    string getHeader() const;

    void print(string input) const;

    void start();

    string getString() const;
    
private:
    string header;
    uint16_t maxStrLen;
    string str;
    Flags flags;
};
}; // namespace Menu
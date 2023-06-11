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

class Select
{
private:
    void getTerminalSize(int& width, int& height);
    void SetCursorVisibility(bool showFlag) const;
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
    void print();

    int maxLength(const vector<string> &strs, int startValue);
    void printLine(string content, int width, bool active, int fill);

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
}; // namespace Menu
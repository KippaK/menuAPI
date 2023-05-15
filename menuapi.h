#include <string>
#include <vector>

using std::string;
using std::vector;


struct Nav {
    char up;
    char down;
    char enter;
};

struct Flags {
    bool stretchX; // overrides center flag
    bool centerX;
    bool centerY;
};

class MenuAPI
{
public:
    MenuAPI();
    MenuAPI(    string aHeader, 
                vector<string> aOptions, 
                Nav aNav,
                Flags Flags);
    ~MenuAPI();

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
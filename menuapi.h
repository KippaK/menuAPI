#include <string>
#include <vector>

using std::string;
using std::vector;


struct Nav {
    char up;
    char down;
    char enter;
};

class MenuAPI
{
public:
    MenuAPI();
    MenuAPI(string aHeader);
    MenuAPI(string aHeader, vector<string> aOptions);
    MenuAPI(string aHeader, vector<string> aOptions, char up, char down, char enter);
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
    void printLine(string content, int width, bool active);

    void start();
    int getValue();
    void setValue(int aValue);

private:
    string header;
    vector<string> options;
    int activePosition;
    int maxOptionLength;
    int value;
    Nav nav;
};
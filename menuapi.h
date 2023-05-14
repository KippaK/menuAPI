#include <string>
#include <vector>

using   std::string, 
        std::vector;



class MenuAPI
{
public:
    MenuAPI();
    MenuAPI(string aHeader);
    MenuAPI(string aHeader, vector<string> aOptions);
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

private:
    string header;
    vector<string> options;
    int activePosition;
    int maxOptionLength;
};
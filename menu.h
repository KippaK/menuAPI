#include "menuapi.h"

struct Nav {
    char up;
    char down;
    char enter;
};

class Menu : MenuAPI
{
public:
    Menu(string aHeader, vector<string> options);
    Menu(string aHeader, vector<string> options, char up, char down, char enter);
    ~Menu();

    void start();
    int getValue();

private:
    Nav nav;
    int value; // Value that has been selected
};
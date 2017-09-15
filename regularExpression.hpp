/*=========This the class to convert infix to postfix regular expression========*/

#ifndef R_EXPRESSION
#define R_EXPRESSION

#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
#include <set>

using namespace std;

class RegularExpression{

private:
    string infixInput;
    string postfixt;
    set<char> binaryOperators;

public:
    RegularExpression();

    bool setInput(string);
    string getInfixInput();
    
    string getPostfixt();

    bool convertPosfix();

    bool check();

};

#endif
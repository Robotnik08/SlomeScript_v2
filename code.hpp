#include <iostream>
#include <string>
#include <vector>
#include <any>
#include "str_tools.hpp"

using namespace std;

class Code;
class Scope;
template <typename T> class Variable;
class Code {
    public:
        vector<string> LineOfCode;
        int location = 0;
        Code (string str, int loc) {
            this->location = loc;
            vector<string> splitLine = str_split(str, " ");
            for (int i = 0; i < splitLine.size(); i++) {
                this->LineOfCode.push_back(splitLine[i]);
            }
        }
};
class Scope {
    public:
        vector<unique_ptr<Code>> codeList;
        int runnerLoc = 0;
        Scope (vector<unique_ptr<Code>> codeList) {
            this->codeList = move(codeList);
        }
};
template <typename T> class Variable {
    public:
        string name;
        T value;
        Variable (string name, T value) {
            this->name = name;
            this->value = value;
        }
};
vector<unique_ptr<Code>> returnCodeList (string fullCode) {
    vector<unique_ptr<Code>> codeList;
    string LineOfCode = "";
    int lineCount = 1;
    for (int i = 0; i < fullCode.length(); i++) {
        if (fullCode[i] == ';') {
            codeList.push_back(make_unique<Code>(LineOfCode, lineCount++));
            LineOfCode = "";
        } else if (fullCode[i] == '\n') {
            LineOfCode += ' ';
        } else {
            LineOfCode += fullCode[i];
        }
    }
    if (LineOfCode.length()) codeList.push_back(make_unique<Code>(LineOfCode, lineCount++));
    return codeList;
};
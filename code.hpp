#include <iostream>
#include <string>
#include <vector>
#include "str_tools.hpp"

using namespace std;

class Code;
class Code {
    public:
        string LineOfCode = "";
        Code (string str) {
            this->LineOfCode = str;
        }
};
vector<unique_ptr<Code>> returnCodeList (string fullCode) {
    vector<unique_ptr<Code>> codeList;
    string LineOfCode = "";
    for (int i = 0; i < fullCode.length(); i++) {
        if (fullCode[i] == ';') {
            codeList.push_back(unique_ptr<Code>(new Code(LineOfCode)));
            LineOfCode = "";
        } else if (fullCode[i] == '\n') {
            LineOfCode += ' ';
        } else {
            LineOfCode += fullCode[i];
        }
    }
    if (LineOfCode.length()) codeList.push_back(unique_ptr<Code>(new Code(LineOfCode)));
    return codeList;
};
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Code;

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
    return codeList;
};
class Code {
    public:
        string LineOfCode = "";
        Code (string str) {
            this->LineOfCode = str;
        }
};
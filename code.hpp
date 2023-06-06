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
        vector<int> locOfEachWord;
        Code (string str, int loc) {
            this->location = loc;
            this->locOfEachWord.push_back(0);
            vector<string> splitLine = str_split(trim_string(str), " ");
            for (int i = 0; i < splitLine.size(); i++) {
                if (splitLine[i][0]) {
                    this->LineOfCode.push_back(splitLine[i]);
                    this->locOfEachWord.push_back(this->locOfEachWord[this->locOfEachWord.size()-1] + splitLine[i].length());
                } 
            }
        }
        string getLineOfCode () {
            string result = "";
            for (int i = 0; i < this->LineOfCode.size(); i++) {
                result += this->LineOfCode[i] + " ";
            }
            return result;
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
#include <iostream>
#include <string>
#include <vector>
#include <any>
#include "str_tools.hpp"


class Code;
class Scope;
template <typename T> class Variable;
class Code {
    public:
        std::vector<std::string> LineOfCode;
        int location = 0;
        std::vector<int> locOfEachWord;
        Code (std::string str, int loc) {
            this->location = loc;
            this->locOfEachWord.push_back(0);
            std::vector<std::string> splitLine = str_split(trim_string(str), " ");
            for (int i = 0; i < splitLine.size(); i++) {
                if (splitLine[i][0]) {
                    this->LineOfCode.push_back(splitLine[i]);
                    this->locOfEachWord.push_back(this->locOfEachWord[this->locOfEachWord.size()-1] + splitLine[i].length());
                } 
            }
        }
        std::string getLineOfCode () {
            std::string result = "";
            for (int i = 0; i < this->LineOfCode.size(); i++) {
                result += this->LineOfCode[i] + " ";
            }
            return result;
        }
};
class Scope {
    public:
        std::vector<std::unique_ptr<Code>> codeList;
        int runnerLoc = 0;
        Scope (std::vector<std::unique_ptr<Code>> codeList) {
            this->codeList = std::move(codeList);
        }
};
template <typename T> class Variable {
    public:
        std::string name;
        T value;
        Variable (std::string name, T value) {
            this->name = name;
            this->value = value;
        }
};
std::vector<std::unique_ptr<Code>> returnCodeList (std::string fullCode) {
    std::vector<std::unique_ptr<Code>> codeList;
    std::string LineOfCode = "";
    int lineCount = 1;
    for (int i = 0; i < fullCode.length(); i++) {
        if (fullCode[i] == ';') {
            codeList.push_back(std::make_unique<Code>(LineOfCode, lineCount++));
            LineOfCode = "";
        } else if (fullCode[i] == '\n') {
            LineOfCode += ' ';
        } else {
            LineOfCode += fullCode[i];
        }
    }
    if (LineOfCode.length()) codeList.push_back(std::make_unique<Code>(LineOfCode, lineCount++));
    return codeList;
};
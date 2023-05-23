#include <iostream>
#include <string>
#include <fstream>
#include "code.hpp"

using namespace std;

class Thread {
    public:
        string fullCode = "";
        vector<unique_ptr<Code>> codeList;
        Thread (char* arg[]) {
            this->fullCode = getFullCode(arg);
            this->codeList = returnCodeList(this->fullCode);
        }
        string getFullCode (char* arg[]) {
            string fullCode = "";
            ifstream file(arg[1]);
            string line;
            while (getline(file, line)) {
                fullCode += line + "\n";
            }
            return fullCode;
        }
};
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
            cout << "Code list: " << endl;
            for (int i = 0; i < this->codeList.size(); i++) {
                cout << "Line " << i << ": " << endl;
                cout << this->codeList[i]->LineOfCode << endl;
            }
        }
        string getFullCode (char* arg[]) {
            string fullCode = "";
            ifstream file(arg[1]);
            if (!file.good()) {
                cout << "File not found." << endl;
                exit(1);
            }
            string line;
            while (getline(file, line)) {
                fullCode += line + "\n";
            }
            return fullCode;
        }
};
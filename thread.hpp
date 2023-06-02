#include <iostream>
#include <string>
#include <fstream>
#include "code.hpp"
#include "error.hpp"

using namespace std;
using namespace err;

class Thread;
class Thread {
    public:
        string fullCode = "";
        vector<unique_ptr<Code>> codeList;
        vector<unique_ptr<Scope>> scopes;
        Thread(char* arg[]) {
            this->fullCode = getFullCode(arg);
            this->codeList = returnCodeList(this->fullCode);

            vector<unique_ptr<Code>> copiedCodeList;
            for (auto& code : this->codeList) {
                copiedCodeList.push_back(move(code));
            }

            this->scopes.push_back(make_unique<Scope>(move(copiedCodeList)));
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
        void ExecuteLine(string line) {
            cout << line << endl;
        }
};
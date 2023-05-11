#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Thread {
    public:
        string fullCode = "";
        Thread (char* arg[]) {
            this->fullCode = getFullCode(arg);
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
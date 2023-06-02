#include <iostream>
#include <string>

using namespace std;

namespace err {
    const int UNKNOWN_ERROR = 0;
    
    const int SYNTAX_ERROR = 1;

    string errorMessages[] = {
        "Unknown Error",
        "Syntax Error"
    };
    void printError (int line, int errCode = 0) {
        cout << line << ": " << errorMessages[errCode] << endl;
        exit(errCode);
    }
}
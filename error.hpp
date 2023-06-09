#include <iostream>
#include <string>


namespace err {
    const int UNKNOWN_ERROR = -1;
    
    const int SYNTAX_ERROR = 1;

    std::string errorMessages[] = {
        "Unknown Error",
        "Syntax Error"
    };
    void printError (int line, int errCode = -1) {
        std::cout << '\n' << line << ": " << errorMessages[std::max(errCode, 0)] << '\n';
        exit(errCode);
    }
}
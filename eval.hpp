#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <variant>

using namespace std;
using namespace err;

//structs
struct PrintVariable {
    template <typename T>
    void operator()(const T& value) const {
        cout << value;
    }
};
struct SysVariable {
    template <typename T>
    void operator()(const T& value) const {
        system(value);
    }
};

//forward declarations
pair<variant<string, int, float, bool>, bool> getNewVariable (string fullLine);


class Parser {
    public:
        Thread* main;
        void parseScript () {
            for (auto& scope : main->scopes) {
                for (auto& code : scope->codeList) {
                    evalSlomeScript(code.get());
                }
            }
        }
        void evalSlomeScript (Code* line) {
            string fullLine = line->getLineOfCode();
            if (!line->LineOfCode.size()) return;
            if (!line->LineOfCode[0].find("SAY")) {
                pair<char, int> nextChar = seekNextChar(fullLine, 3);
                if (nextChar.first == '(') {
                    string parametersFull = str_full_parentheses(fullLine, nextChar.second, '(', ')');
                    vector<string> parameters = splitIntoParameters(str_trim(parametersFull));
                    for (auto& parameter : parameters) {
                        pair<variant<string, int, float, bool>, bool> coutValue = getNewVariable(parameter);
                        if (!coutValue.second) printError(line->location, SYNTAX_ERROR);
                        visit(PrintVariable{}, coutValue.first);
                    }
                } else {
                    printError(line->location, SYNTAX_ERROR);
                }
            } else if (!line->LineOfCode[0].find("PAUSE")) {
                pair<char, int> nextChar = seekNextChar(fullLine, 5);
                if (nextChar.first == '(') {
                    string parametersFull = str_full_parentheses(fullLine, nextChar.second, '(', ')');
                    vector<string> parameters = splitIntoParameters(str_trim(parametersFull));
                    if (parameters.size()) printError(line->location, SYNTAX_ERROR);
                    system("pause");
                } else {
                    printError(line->location, SYNTAX_ERROR);
                }
            } else {
                printError(line->location, UNKNOWN_ERROR);
            }
        }
        //init
        Parser (Thread* t) : main(t) {
            this->parseScript();
        }
};
pair<variant<string, int, float, bool>, bool> getNewVariable (string fullLine) {
    int currentLoc = 0;
    if (fullLine[currentLoc] == '\'' || fullLine[currentLoc] == '"') {
        string result = getFullString(fullLine, 0, fullLine[currentLoc]);
        return make_pair(str_trim(result), true);
    }
    return make_pair(0, false);
}
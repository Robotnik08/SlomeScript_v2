#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <variant>

//structs
struct PrintVariable {
    template <typename T>
    void operator()(const T& value) const {
        std::cout << value;
    }
};
struct SysVariable {
    template <typename T>
    void operator()(const T& value) const {
        system(value);
    }
};

//forward declarations
std::pair<std::variant<std::string, int, float, bool>, bool> getNewVariable (std::string fullLine);


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
            std::string fullLine = line->getLineOfCode();
            if (!line->LineOfCode.size()) return;
            if (!line->LineOfCode[0].find("SAY")) {
                std::pair<char, int> nextChar = seekNextChar(fullLine, 3);
                if (nextChar.first == '(') {
                    std::string parametersFull = str_full_parentheses(fullLine, nextChar.second, '(', ')');
                    std::vector<std::string> parameters = splitIntoParameters(str_trim(parametersFull));
                    for (auto& parameter : parameters) {
                        std::pair<std::variant<std::string, int, float, bool>, bool> coutValue = getNewVariable(parameter);
                        if (!coutValue.second) err::printError(line->location, err::SYNTAX_ERROR);
                        visit(PrintVariable{}, coutValue.first);
                    }
                } else {
                    err::printError(line->location, err::SYNTAX_ERROR);
                }
            } else if (!line->LineOfCode[0].find("PAUSE")) {
                std::pair<char, int> nextChar = seekNextChar(fullLine, 5);
                if (nextChar.first == '(') {
                    std::string parametersFull = str_full_parentheses(fullLine, nextChar.second, '(', ')');
                    std::vector<std::string> parameters = splitIntoParameters(str_trim(parametersFull));
                    if (parameters.size()) err::printError(line->location, err::SYNTAX_ERROR);
                    system("pause");
                } else {
                    err::printError(line->location, err::SYNTAX_ERROR);
                }
            } else {
                err::printError(line->location, err::UNKNOWN_ERROR);
            }
        }
        //init
        Parser (Thread* t) : main(t) {
            this->parseScript();
        }
};
std::pair<std::variant<std::string, int, float, bool>, bool> getNewVariable (std::string fullLine) {
    int currentLoc = 0;
    if (fullLine[currentLoc] == '\'' || fullLine[currentLoc] == '"') {
        std::string result = getFullString(fullLine, 0, fullLine[currentLoc]);
        return make_pair(str_trim(result), true);
    }
    return std::make_pair(0, false);
}
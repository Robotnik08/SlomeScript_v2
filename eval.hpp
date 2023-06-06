#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <variant>

using namespace std;
using namespace err;

//structs
struct PrintVisitor {
    template <typename T>
    void operator()(const T& value) const {
        cout << value;
    }
};

//forward declarations
pair<variant<string, int, float, bool>, int> getNewVariable (Code* line, int startloc);


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
            try {
                if (!line->LineOfCode.size()) return;
                if (!line->LineOfCode[0].find("SAY")) {
                    pair<variant<string, int, float, bool>, int> coutValue = getNewVariable(line, line->locOfEachWord[1]+1);
                    if (!coutValue.second) printError(line->location, SYNTAX_ERROR);
                    visit(PrintVisitor{}, coutValue.first);
                } else {
                    printError(line->location, SYNTAX_ERROR);
                }

            } catch (const std::exception& e) {
                printError(line->location, SYNTAX_ERROR);
            }
        }
        //init
        Parser (Thread* t) : main(t) {
            this->parseScript();
        }
};
pair<variant<string, int, float, bool>, int> getNewVariable (Code* line, int startloc) {
    string fullLine = line->getLineOfCode();
    int currentLoc = startloc;
    if (fullLine[currentLoc] == '\'' || fullLine[currentLoc] == '"') {
        string result = getFullString(fullLine, startloc, fullLine[currentLoc]);
        return make_pair(str_trim(result), currentLoc);
    }
    return make_pair(0, NULL);
}
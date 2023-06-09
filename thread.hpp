#include <iostream>
#include <string>
#include <fstream>
#include "code.hpp"
#include "error.hpp"

class Parser;
class Thread;
class Thread {
    public:
        std::string fullCode = "";
        std::vector<std::unique_ptr<Code>> codeList;
        std::vector<std::unique_ptr<Scope>> scopes;
        std::unique_ptr<Parser> parser;
        Thread(char* arg[]) {
            this->fullCode = getFullCode(arg);
            this->codeList = returnCodeList(this->fullCode);

            std::vector<std::unique_ptr<Code>> copiedCodeList;
            for (auto& code : this->codeList) {
                copiedCodeList.push_back(move(code));
            }

            this->scopes.push_back(std::make_unique<Scope>(move(copiedCodeList)));
            this->parser = std::make_unique<Parser>(this);
        }
        std::string getFullCode (char* arg[]) {
            std::string fullCode = "";
            std::ifstream file("main.slome");
            if (!file.good()) {
                std::cout << "File not found.\n";
                exit(1);
            }
            std::string line;
            while (getline(file, line)) {
                fullCode += line + "\n";
            }
            return fullCode;
        }
        void ExecuteLine(std::string line) {
            std::cout << line << '\n';
        }
};
#include "eval.hpp"
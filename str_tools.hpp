#include <vector>
#include <string>
#include <iostream>


char getEscapeChar (char in);

std::string str_full_parentheses(std::string input, int pos = 0, char parenthesesChar = '(', char endParenthesesChar = ')') {
    std::string result = "";
    int parentheses = 0;
    bool foundParentheses = false;
    char str_char = '"';
    bool inString = false;
    while (pos < input.size()-1) {
        char currentChar = input[pos++];
        if (currentChar == '"' || currentChar == '\'') {
            if (inString) {
                if (str_char == currentChar && input[pos - 2] != '\\') {
                    inString = false;
                }
            } else {
                inString = true;
                str_char = currentChar;
            }
            result += currentChar;
            continue;
        }
        if (foundParentheses) {
            result += currentChar;
            if (currentChar == endParenthesesChar) {
                parentheses--;
                if (!parentheses) {
                    return result;
                }
            } else if (currentChar == parenthesesChar) {
                parentheses++;
            }
        } else if (currentChar == parenthesesChar) {
            result += currentChar;
            foundParentheses = true;
            parentheses++;
        }
    }
    return "";
}
std::string getFullString (std::string input, int pos = 0, char strChar = '"') {
    std::string result;
    bool foundStr = false;
    while (pos < input.size()) {
        char currentChar = input[pos++];
        if (foundStr) {
            while (currentChar == '\\') {
                result += getEscapeChar(input[pos++]);
                currentChar = input[pos++];
            }
            result += currentChar;
            if (currentChar == strChar) return result;
        } else if (currentChar == strChar) {
            result += currentChar;
            foundStr = true;
        }
    }
    return NULL;
}
std::vector<std::string> str_split (std::string input, std::string delimeter) {
    std::vector<std::string> result;
    int pos = 0;
    int delimeterPos = 0;
    std::string currentString = "";
    while (pos < input.size()) {
        char currentChar = input[pos++];
        if (currentChar == delimeter[delimeterPos]) {
            delimeterPos++;
            if (delimeterPos == delimeter.size()) {
                result.push_back(currentString);
                currentString = "";
                delimeterPos = 0;
            }
        } else {
            currentString += currentChar;
            delimeterPos = 0;
        }
    }
    if (currentString.size()) result.push_back(currentString);
    return result;
}
std::string trim_string(std::string str, std::string target = " \n") {
    size_t start = 0;
    size_t end = str.length();
    while (start < end && target.find(str[start]) != std::string::npos) {
        ++start;
    }
    while (end > start && target.find(str[end-1]) != std::string::npos) {
        --end;
    }
    return str.substr(start, end - start);
}
std::string str_trim (std::string input, int amount = 1) {
    std::string result = "";
    for (int i = amount; i < input.length() - amount; i++) {
        result += input[i];
    }
    return result;
}
std::pair<char, int> seekNextChar (std::string input, int start_pos = 0) {
    int pos = start_pos;
    std::pair <char, int> result;
    while (pos < input.size()) {
        if (input[pos] != '\n' && input[pos] != ' ') {
            return std::pair<char, int>(input[pos], pos);
        }
        pos++;
    }
    return std::pair<char, int>(' ', NULL);
}
std::vector<std::string> splitIntoParameters (std::string str) {
    std::vector<std::string> result;
    int pos = 0;
    std::string add = "";
    bool inString = false;
    char str_char = '"';
    while (pos < str.size()) {
        add += str[pos++];
        if (!inString) {
            if (str[pos] == ',') {
                result.push_back(add);
                add = "";
                pos++;
                while (str[pos] == ' ') {
                    pos++;
                }
            } else if (str[pos-1] == '"' || str[pos-1] == '\'') {
                inString = false;
                str_char = str[pos-1];
            }
        } else {
            if (str[pos-1] == str_char && str[pos - 2] != '\\') {
                inString = true;
            }
        }
    }
    if (add.size()) result.push_back(add);
    return result;
}
char getEscapeChar (char in) {
    switch (in) {
        case 'n':
            return '\n';
        case 't':
            return '\t';
        case 'r':
            return '\r';
        case 'b':
            return '\b';
        case 'a':
            return '\a';
        case 'v':
            return '\v';
        case 'f':
            return '\f';
        case '\\':
            return '\\';
        case '\'':
            return '\'';
        case '"':
            return '"';
        case '0':
            return '\0';
        default:
            return in;
    }
}
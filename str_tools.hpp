#include <vector>
#include <string>
#include <iostream>

using namespace std;

string str_full_parentheses(string input, int pos = 0, char parenthesesChar = '(', char endParenthesesChar = ')') {
    string result;
    int parentheses = 0;
    bool foundParentheses = false;
    char str_char = '"';
    bool inString = false;
    while (pos < input.size()) {
        char currentChar = input[pos++];
        if (currentChar == '"' || currentChar == '\'' || currentChar == '`' ) {
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
        }
    }
    return NULL;
}
string getFullString (string input, int pos = 0, char strChar = '"') {
    string result;
    bool foundStr = false;
    while (pos < input.size()) {
        char currentChar = input[pos++];
        if (foundStr) {
            result += currentChar;
            if (currentChar == strChar && input[pos - 2] != '\\') {
                return result;
            }
        } else if (currentChar == strChar) {
            result += currentChar;
            foundStr = true;
        }
    }
    return NULL;
}
vector<string> str_split (string input, string delimeter) {
    vector<string> result;
    int pos = 0;
    int delimeterPos = 0;
    string currentString = "";
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
string trim_string(string str, string target = " \n") {
    size_t start = 0;
    size_t end = str.length();
    while (start < end && target.find(str[start]) != string::npos) {
        ++start;
    }
    while (end > start && target.find(str[end-1]) != string::npos) {
        --end;
    }
    return str.substr(start, end - start);
}
string str_trim (string input, int amount = 1) {
    string result = "";
    for (int i = amount; i < input.length() - amount; i++) {
        result += input[i];
    }
    return result;
}
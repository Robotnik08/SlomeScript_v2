#include <vector>
#include <string>
#include <iostream>

using namespace std;

string str_full_parentheses(string input) {
    string result;
    int pos = 0;
    int parentheses = 0;
    bool foundParentheses = false;
    while (pos < input.size()) {
        char currentChar = input[pos++];
        if (foundParentheses) {
            result += currentChar;
            if (currentChar == ')') {
                parentheses--;
                if (!parentheses) {
                    return result;
                }
            } else if (currentChar == '(') {
                parentheses++;
            }
        } else if (currentChar == '(') {
            result += currentChar;
            foundParentheses = true;
        }
    }
    return result;
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
string trim_string (string input, char targetChar = ' ') {
    string result = "";
    int pos = 0;
    while (pos < input.size()) {
        char currentChar = input[pos++];
        if (currentChar != targetChar) {
            result += currentChar;
        }
    }
    return result;
}
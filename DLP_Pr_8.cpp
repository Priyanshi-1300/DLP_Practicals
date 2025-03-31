#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <iomanip>

using namespace std;

map<char, vector<string>> grammar = {
    {'S', {"ABC", "D"}},
    {'A', {"a", "n"}},
    {'B', {"b", "n"}},
    {'C', {"(S)", "c", "n"}},
    {'D', {"A C"}}
};

map<char, vector<char>> firstSet = {
    {'S', {'a', 'b', '(', 'c'}},
    {'A', {'a', 'n'}},
    {'B', {'b', 'n'}},
    {'C', {'(', 'c'}},
    {'D', {'a', '(', 'c', 'n'}}
};

map<char, vector<char>> followSet = {
    {'S', {'$', ')'}},
    {'A', {'b', '(', 'c', '$', ')'}},
    {'B', {'(', 'c', '$', ')'}},
    {'C', {'$', ')'}},
    {'D', {'$', ')'}}
};

map<pair<char, char>, string> parsingTable;

void constructParsingTable() {
    for (auto& rule : grammar) {
        char nonTerminal = rule.first;
        for (string production : rule.second) {
            if (production == "ε") {
                for (char terminal : followSet[nonTerminal]) {
                    parsingTable[{nonTerminal, terminal}] = "ε";
                }
            } else {
                for (char terminal : firstSet[production[0]]) {
                    if (terminal != 'ε') {
                        parsingTable[{nonTerminal, terminal}] = production;
                    }
                }
            }
        }
    }
}

bool isLL1() {
    for (auto& entry : parsingTable) {
        auto key = entry.first;
        if (parsingTable.count(key) > 1) {
            return false;
        }
    }
    return true;
}

bool validateString(string input) {
    input += "$";
    stack<char> parserStack;
    parserStack.push('$');
    parserStack.push('S');

    int i = 0;
    while (!parserStack.empty()) {
        char top = parserStack.top();
        char currentInput = input[i];

        if (top == currentInput) {
            parserStack.pop();
            i++;
        } else if (parsingTable.find({top, currentInput}) != parsingTable.end()) {
            parserStack.pop();
            string production = parsingTable[{top, currentInput}];

            if (production != "ε") {
                for (int j = production.length() - 1; j >= 0; j--) {
                    parserStack.push(production[j]);
                }
            }
        } else {
            return false;
        }
    }
    return i == input.length();
}

void displayParsingTable() {
    cout << "\nPredictive Parsing Table:\n";
    cout << "------------------------------------\n";
    cout << "| Non-Terminal | Terminal | Production |\n";
    cout << "------------------------------------\n";
    for (auto& entry : parsingTable) {
        cout << "| " << setw(12) << entry.first.first << " | "
             << setw(8) << entry.first.second << " | "
             << setw(10) << entry.second << " |\n";
    }
    cout << "------------------------------------\n";
}

int main() {
    constructParsingTable();
    displayParsingTable();

    if (isLL1()) {
        cout << "\nThe grammar is LL(1).\n";
    } else {
        cout << "\nThe grammar is NOT LL(1).\n";
        return 0;
    }

    vector<string> testCases = {"abc", "ac", "(abc)", "c", "ac", "a", "()", "(ab)", "abcabc", "b"};
    for (string test : testCases) {
        cout << "Testing \"" << test << "\": " << (validateString(test) ? "Valid string" : "Invalid string") << endl;
    }

    return 0;
}

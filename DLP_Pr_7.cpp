#include <iostream>
#include <cstring>

using namespace std;

const int MAX = 10; // Maximum number of non-terminals
const int MAX_SYMBOLS = 20; // Maximum number of symbols in FIRST/FOLLOW sets

class FirstFollow {
private:
    char nonTerminals[MAX] = {'S', 'A', 'B', 'C', 'D'};
    char firstSet[MAX][MAX_SYMBOLS];
    char followSet[MAX][MAX_SYMBOLS];
    char grammar[MAX][3][MAX_SYMBOLS] = {
        {"ABC", "D", ""},  // Productions for S
        {"a", "", ""},     // Productions for A (ε is represented as "")
        {"b", "", ""},     // Productions for B (ε is represented as "")
        {"(S)", "c", ""},  // Productions for C
        {"AC", "", ""}     // Productions for D
    };

    int n = 5; // Number of non-terminals

    // Helper to add symbols in FIRST or FOLLOW sets
    bool addSymbol(char* set, char symbol) {
        if (strchr(set, symbol) == NULL) {
            int len = strlen(set);
            set[len] = symbol;
            set[len + 1] = '\0';
            return true;
        }
        return false;
    }

    // Get index of a non-terminal
    int getIndex(char nonTerminal) {
        for (int i = 0; i < n; i++) {
            if (nonTerminals[i] == nonTerminal)
                return i;
        }
        return -1;
    }

public:
    FirstFollow() {
        for (int i = 0; i < n; i++) {
            firstSet[i][0] = '\0';
            followSet[i][0] = '\0';
        }
        addSymbol(followSet[0], '$'); // Add '$' to Follow(S)
    }

    // Compute FIRST sets
  void computeFirst() {
    bool updated;
    do {
        updated = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 3; j++) {
                char* production = grammar[i][j];

                // If the production is empty, add n
                if (strlen(production) == 0) {
                    updated |= addSymbol(firstSet[i], 'n');
                } else {
                    bool containsEpsilon = true;
                    for (int k = 0; production[k] != '\0'; k++) {
                        char symbol = production[k];

                        if (isupper(symbol)) { // If it's a non-terminal
                            int idx = getIndex(symbol);

                            // Add everything from FIRST except n
                            for (int l = 0; firstSet[idx][l] != '\0'; l++) {
                                if (firstSet[idx][l] != 'n') {
                                    updated |= addSymbol(firstSet[i], firstSet[idx][l]);
                                }
                            }

                            // If FIRST does not have n, stop processing
                            if (strchr(firstSet[idx], 'n') == NULL) {
                                containsEpsilon = false;
                                break;
                            }
                        } else { // Terminal, add directly to FIRST set
                            updated |= addSymbol(firstSet[i], symbol);
                            containsEpsilon = false;
                            break;
                        }
                    }

                    // Only add n if all symbols in the production can be n
                    if (containsEpsilon) {
                        updated |= addSymbol(firstSet[i], 'n');
                    }
                }
            }
        }
    } while (updated);
}

    // Compute FOLLOW sets
    void computeFollow() {
        bool updated;
        do {
            updated = false;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 3; j++) {
                    char* production = grammar[i][j];
                    int len = strlen(production);
                    for (int k = 0; k < len; k++) {
                        char symbol = production[k];
                        if (isupper(symbol)) {
                            int idx = getIndex(symbol);
                            bool epsilonFound = true;

                            for (int l = k + 1; l < len && epsilonFound; l++) {
                                char nextSymbol = production[l];
                                epsilonFound = false;

                                if (isupper(nextSymbol)) {
                                    int nextIdx = getIndex(nextSymbol);
                                    for (int m = 0; firstSet[nextIdx][m] != '\0'; m++) {
                                        if (firstSet[nextIdx][m] != 'n') {
                                            updated |= addSymbol(followSet[idx], firstSet[nextIdx][m]);
                                        }
                                    }
                                    if (strchr(firstSet[nextIdx], 'n'))
                                        epsilonFound = true;
                                } else {
                                    updated |= addSymbol(followSet[idx], nextSymbol);
                                    epsilonFound = false;
                                }
                            }

                            if (epsilonFound || k == len - 1) {
                                for (int m = 0; followSet[i][m] != '\0'; m++) {
                                    updated |= addSymbol(followSet[idx], followSet[i][m]);
                                }
                            }
                        }
                    }
                }
            }
        } while (updated);
    }

    // Display FIRST and FOLLOW sets
    void displaySets() {
        cout << "First Sets:\n";
        for (int i = 0; i < n; i++) {
            cout << "First(" << nonTerminals[i] << ") = { ";
            for (int j = 0; firstSet[i][j] != '\0'; j++) {
                cout << firstSet[i][j] << " ";
            }
            cout << "}\n";
        }

        cout << "\nFollow Sets:\n";
        for (int i = 0; i < n; i++) {
            cout << "Follow(" << nonTerminals[i] << ") = { ";
            for (int j = 0; followSet[i][j] != '\0'; j++) {
                cout << followSet[i][j] << " ";
            }
            cout << "}\n";
        }
    }
};

int main() {
    FirstFollow ff;
    ff.computeFirst();
    ff.computeFollow();
    ff.displaySets();
    return 0;
}

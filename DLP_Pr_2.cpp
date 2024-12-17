#include <iostream>
using namespace std;

const int MAX_STATES = 10;     // Maximum No Of States
const int MAX_SYMBOLS = 2;     // Fixed Input Symbols: 'a' and 'b'

int main() {
    int numStates, initialState, numAcceptingStates, acceptingStates[MAX_STATES];
    int transitionTable[MAX_STATES][MAX_SYMBOLS] = {0};  // Transition Table

    cout << "Enter No Of States: ";
    cin >> numStates;

    cout << "Enter Initial State: ";
    cin >> initialState;

    cout << "Enter No Of Accepting States: ";
    cin >> numAcceptingStates;

    cout << "Enter Accepting States: ";
    for (int i = 0; i < numAcceptingStates; i++) {
        cin >> acceptingStates[i];
    }

    // Transition Table
    cout << "Enter Transitions Table In The Format: current_state input_symbol(a/b) next_state" << endl;
    cout << "Type -1 To Stop Input" << endl;
    while (true) {
        int currentState, nextState;
        char inputSymbol;
        cin >> currentState;

        if (currentState == -1) break;  // Stop input

        cin >> inputSymbol >> nextState;

        int symbolIndex = (inputSymbol == 'a') ? 0 : 1;  // Map 'a' -> 0, 'b' -> 1
        transitionTable[currentState][symbolIndex] = nextState;
    }

    string inputString;
    cout << "Enter The String To Validate : ";
    cin >> inputString;

    int currentState = initialState;

    for (int i = 0; i < inputString.length(); i++) {
        char symbol = inputString[i];
        int symbolIndex = (symbol == 'a') ? 0 : 1;

        if (transitionTable[currentState][symbolIndex] == 0) {
            cout << "The string is INVALID." << endl;
            return 0;
        }

        currentState = transitionTable[currentState][symbolIndex];
    }

    // Check if the current state is an accepting state
    bool isValid = false;
    for (int i = 0; i < numAcceptingStates; i++) {
        if (currentState == acceptingStates[i]) {
            isValid = true;
            break;
        }
    }

    if (isValid) {
        cout << "The string is VALID." << endl;
    } else {
        cout << "The string is INVALID." << endl;
    }

    return 0;
}

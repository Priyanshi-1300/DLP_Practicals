#include<iostream>
#include <string>

using namespace std;

class RecursiveDescentParser{
private:
    string input;
    int index;

    char lookahead() {
        if (index < input.length())
            return input[index];
        return '\0';
    }

    void incre() {
        index++;
    }

    // S → ( L ) | a
    bool S() {
        if (lookahead() == '(') {
            incre();
            if (L() && lookahead() == ')') {
                incre();
                return true;
            }
            return false;
        } else if (lookahead() == 'a') {
            incre();
            return true;
        }
        return false;
    }

    // L → S L'
    bool L() {
        if (S()) {
            return LPrime();
        }
        return false;
    }

    // L' → , S L' | ε
    bool LPrime() {
        if (lookahead() == ',') {
            incre();
            if (S()) {
                return LPrime();
            }
            return false;
        }
        return true; // ε
    }

    public:
    RecursiveDescentParser(string str) : input(str), index(0) {}

    bool parse() {
        if (S() && index == input.length()) {
            return true;
        }
        return false;
    }
};

int main(){
    string input;
    cout<<"Enter The Input String : ";
    getline(cin, input);

    RecursiveDescentParser parser(input);
    if (parser.parse()) {
        cout << "Valid string" << endl;
    } else {
        cout << "Invalid string" << endl;
    }

    return 0;
}


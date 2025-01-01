#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Function Prototypes
bool isDelimiter(char ch);
bool isOperator(char ch);
bool validIdentifier(char str[]);
bool isKeyword(char str[]);
bool isInteger(char str[]);
bool isRealNumber(char str[]);
void subString(char str[], int left, int right, char result[]);
void removeComments(char str[], char result[]);
void parse(char str[]);

// Predefined arrays for operators, keywords, and punctuation
const char* operators[] = {"+", "-", "*", "/", ">", "<", "="};
const char* keywords[] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "inline", "int",
    "long", "register", "restrict", "return", "short",
    "signed", "sizeof", "static", "struct", "switch",
    "typedef", "union", "unsigned", "void", "volatile", "while"
};
const char punctuations[] = {',', ';', '(', ')', '[', ']', '{', '}'};
const int numOperators = sizeof(operators) / sizeof(operators[0]);
const int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
const int numPunctuations = sizeof(punctuations) / sizeof(punctuations[0]);

// Returns 'true' if the character is a DELIMITER.
bool isDelimiter(char ch) {
    for (int i = 0; i < numPunctuations; i++) {
        if (ch == punctuations[i])
            return true;
    }
    return (ch == ' ' || isOperator(ch));
}

// Returns 'true' if the character is an OPERATOR.
bool isOperator(char ch) {
    for (int i = 0; i < numOperators; i++) {
        if (ch == operators[i][0])
            return true;
    }
    return false;
}

// Returns 'true' if the string is a VALID IDENTIFIER.
bool validIdentifier(char str[]) {
    if ((str[0] >= '0' && str[0] <= '9') || isDelimiter(str[0]))
        return false;
    return true;
}

// Returns 'true' if the string is a KEYWORD.
bool isKeyword(char str[]) {
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return true;
    }
    return false;
}

// Returns 'true' if the string is an INTEGER.
bool isInteger(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}

// Returns 'true' if the string is a REAL NUMBER.
bool isRealNumber(char str[]) {
    bool hasDecimal = false;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == '.') {
            if (hasDecimal)
                return false;
            hasDecimal = true;
        } else if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }
    return hasDecimal;
}

// Extracts the SUBSTRING.
void subString(char str[], int left, int right, char result[]) {
    int j = 0;
    for (int i = left; i <= right; i++) {
        result[j++] = str[i];
    }
    result[j] = '\0';
}

// Function to remove comments from the code
void removeComments(char str[], char result[]) {
    int j = 0;
    bool singleLineComment = false, multiLineComment = false;
    for (int i = 0; str[i] != '\0'; i++) {
        if (singleLineComment && str[i] == '\n') {
            singleLineComment = false;
        } else if (multiLineComment && str[i] == '*' && str[i + 1] == '/') {
            multiLineComment = false;
            i++;
        } else if (!singleLineComment && !multiLineComment) {
            if (str[i] == '/' && str[i + 1] == '/') {
                singleLineComment = true;
                i++;
            } else if (str[i] == '/' && str[i + 1] == '*') {
                multiLineComment = true;
                i++;
            } else {
                result[j++] = str[i];
            }
        }
    }
    result[j] = '\0';
}

// Parsing the input STRING.
void parse(char str[]) {
    int left = 0, right = 0;
    int len = strlen(str);
    char subStr[100];

    while (right <= len && left <= right) {
        if (!isDelimiter(str[right]))
            right++;

        if (isDelimiter(str[right]) && left == right) {
            if (isOperator(str[right]))
                printf("'%c' IS AN OPERATOR\n", str[right]);
            else {
                for (int i = 0; i < numPunctuations; i++) {
                    if (str[right] == punctuations[i]) {
                        printf("'%c' IS A PUNCTUATION\n", str[right]);
                        break;
                    }
                }
            }
            right++;
            left = right;
        } else if ((isDelimiter(str[right]) && left != right) || (right == len && left != right)) {
            subString(str, left, right - 1, subStr);

            if (isKeyword(subStr))
                printf("'%s' IS A KEYWORD\n", subStr);
            else if (isInteger(subStr))
                printf("'%s' IS AN INTEGER\n", subStr);
            else if (isRealNumber(subStr))
                printf("'%s' IS A REAL NUMBER\n", subStr);
            else if (validIdentifier(subStr))
                printf("'%s' IS A VALID IDENTIFIER\n", subStr);
            else
                printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);

            left = right;
        }
    }
}

int main() {
    char str[200] = "int main(){\n\tint a=5,7H;// assign value\n\tchar b='x';\n\t/*return\nvalue*/\n\treturn a+b;}";
    char noComments[200];

    // Remove comments
    removeComments(str, noComments);
    printf("Code without comments:\n%s\n", noComments);

    // Parse the code
    parse(noComments);

    return 0;
}




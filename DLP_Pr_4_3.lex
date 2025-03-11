%{
#include <stdio.h>
#include <string.h>

int char_count = 0, word_count = 0, line_count = 0;
int whitespace_count = 0, tab_count = 0, special_char_count = 0;
int keyword_count = 0, identifier_count = 0, constant_count = 0;

char *keywords[] = {"int", "char", "float", "double", "return", "if", "else", "while", "for", "switch", "case", "break", "continue", "void", "static", "struct", "typedef", "union", "default", "do", "const", "sizeof", "short", "long", "signed", "unsigned"};
int keyword_size = sizeof(keywords) / sizeof(keywords[0]);

int is_keyword(char *word) {
    for (int i = 0; i < keyword_size; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
%}

%%
\n            { line_count++; }
[ \t]        { whitespace_count++;  if (yytext[0] == '\t') tab_count++; }
[_a-zA-Z][_a-zA-Z0-9]* {
                if (is_keyword(yytext)) {
                    keyword_count++;
                    printf("%s is a KEYWORD\n", yytext);
                } else {
                    identifier_count++;
                    printf("%s is a VALID IDENTIFIER\n", yytext);
                }
                word_count++;
                char_count += yyleng;
            }
[0-9]+(\.[0-9]+)? { constant_count++; char_count += yyleng; word_count++; printf("%s is a REAL NUMBER\n", yytext); }
[!@#$%^&*()_+={}|:";'<>?,./\\`~\[\]-] { special_char_count++; char_count++; printf("%s is a Special Character \n", yytext); }
.            { char_count++; }
%%

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }
    yyin = file;
    yylex();
    fclose(file);
    
    printf("Characters : %d\n", char_count);
    printf("Words : %d\n", word_count);
    printf("Lines : %d\n", line_count);
    printf("Whitespaces : %d\n", whitespace_count);
    printf("Tab spaces : %d\n", tab_count);
    printf("Special characters : %d\n", special_char_count);
    printf("Keywords : %d\n", keyword_count);
    printf("Identifiers : %d\n", identifier_count);
    printf("Constants : %d\n", constant_count);
    return 0;
}

int yywrap() {
    return 1;
}

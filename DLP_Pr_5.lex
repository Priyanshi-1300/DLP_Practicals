%{
#include <stdio.h>
#include <string.h>

int keyword_count = 0, identifier_count = 0, integer_count = 0, real_number_count = 0;
int operator_count = 0, punctuation_count = 0, comment_count = 0;

char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "inline", "int",
    "long", "register", "restrict", "return", "short",
    "signed", "sizeof", "static", "struct", "switch",
    "typedef", "union", "unsigned", "void", "volatile",
    "while"
};

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

"//".*                { comment_count++; } 
"/\*"([^*]|\*+[^*/])*"\*/"  { comment_count++; } 

[a-zA-Z_][a-zA-Z0-9_]* {
    if (is_keyword(yytext)) {
        keyword_count++;
        printf("%s is a KEYWORD\n", yytext);
    } else {
        identifier_count++;
        printf("%s is a VALID IDENTIFIER\n", yytext);
    }
}

[0-9]+                { integer_count++; printf("%s is an INTEGER\n", yytext); }
[0-9]+\.[0-9]+       { real_number_count++; printf("%s is a REAL NUMBER\n", yytext); }

[\+\-\*/><=]         { operator_count++; printf("%s is an OPERATOR\n", yytext); }

[\,;\(\)\[\]\{\}]  { punctuation_count++; printf("%s is a PUNCTUATION\n", yytext); }

[ \t\n]+              { }

.                      { printf("%s is NOT A VALID IDENTIFIER\n", yytext); }

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

    printf("\nSummary:\n");
    printf("Keywords: %d\n", keyword_count);
    printf("Identifiers: %d\n", identifier_count);
    printf("Integers: %d\n", integer_count);
    printf("Real Numbers: %d\n", real_number_count);
    printf("Operators: %d\n", operator_count);
    printf("Punctuations: %d\n", punctuation_count);
    printf("Comments: %d\n", comment_count);

    return 0;
}

int yywrap() {
    return 1;
}
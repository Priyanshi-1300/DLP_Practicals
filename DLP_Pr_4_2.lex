%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%%
[Cc]harusat    printf("university");
.|\n           printf("%s", yytext);
%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

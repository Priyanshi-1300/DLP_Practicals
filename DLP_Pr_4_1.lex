%{
#include<stdio.h>
#include<stdlib.h>
%}

%%
[0-9]+  { printf("%s\n", yytext); }
.       { } // Ignore other characters

%%

int main()
{
    printf("Enter a string: \n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
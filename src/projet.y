%{
#include <stdio.h>
int yylex();
void lex_free();
void yyerror(char *);
FILE *yyin;
FILE *yyout;
tab tds = { .debut = NULL,.fin =NULL};
%}

%left '+' '-'
%left '*' '/'

%%

%%

int main(){
	yyparse();
	return 0;
}

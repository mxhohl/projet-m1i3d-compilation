%{

#include <string.h>
#include <stdio.h>

#include "c_grammar.tab.h"

%}

%option noyywrap
%option yylineno

EXPONENT        [eE][+-]?[0-9]+

INTEGER         [+-]?[0-9]+
DOUBLE          {INTEGER}(("."[0-9]*{EXPONENT}?)|({EXPONENT}))

IDENTIFICATOR   [a-zA-Z_][a-zA-Z0-9_]*

UNICOMMENT      "//".*
MULCOMMENT      "/*"([^*]*[*]+[^*/])*[^*]*[*]+"/"
COMMENT         ({UNICOMMENT})|({MULCOMMENT})

MAIN            "int main()"

QUOTED_STR      \"(\\.|[^\\"])*\"
PRINT           "printf("{QUOTED_STR}[^)]*")"

%%

<<EOF>>         { return EOFILE; }

{COMMENT}       { /* On ignore les commentaires */ }

"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"for"           { return FOR; }

{PRINT}         { size_t len = yyleng -7;
                  char* content = malloc(sizeof(char) * len);
                  sscanf(yytext, "printf(%s)", content);
                  yylval.str = content;
                  return PRINTF; }

{MAIN}          { return MAIN; }

int             { return TYPE_INT; }
double          { return TYPE_DOUBLE; }

{INTEGER}       { yylval.integer = atoi(yytext); 
                  return STATIC_INT; }
{DOUBLE}        { yylval.floating = atof(yytext);
                  return STATIC_DOUBLE; }

{IDENTIFICATOR} { yylval.str = strdup(yytext);
                  return ID; }

"+"             { return OP_PLUS; }
"-"             { return OP_MINUS; }
"*"             { return OP_MULTIPLY; }
"/"             { return OP_DIVIDE; }
"++"            { return OP_INCREMENT; }
"--"            { return OP_DECREMENT; }

"=="            { return OP_EQ; }
"!="            { return OP_NEQ; }
"&&"            { return OP_AND; }
"||"            { return OP_OR; }
"<"             { return OP_LOWER; }
"<="            { return OP_LOWER_EQ; }
">"             { return OP_GREATER; }
">="            { return OP_GREATER_EQ; }
"!"             { return OP_NOT; }

";"             { return SEMICOLON; }
","             { return COMMA; }
"="             { return EQUAL; }
"("             { return LPARENTHESIS; }
")"             { return RPARENTHESIS; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }
"["             { return LBRACKET; }
"]"             { return RBRACKET; }

[ \t\n]         { /* on saute les espaces */ }
.	            { fflush(stdout);
                  fprintf(stderr, 
                          "\033[1;33mCaractère '%c' inconnu "
                          "à la ligne %d\033[0m\n",
                          *yytext,
                          yylineno
                  ); }

%%


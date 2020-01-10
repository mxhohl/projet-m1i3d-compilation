%{

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "c_grammar.tab.h"

void lexError(const char*, ...);

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
RETURN          "return"

QUOTED_STR      \"(\\.|[^\\"])*\"
PRINT           "printf("{QUOTED_STR}[^)]*")"

%%

<<EOF>>         { return EOFILE; }

{COMMENT}       { /* On ignore les commentaires */ }

"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"for"           { return FOR; }

{PRINT}         { size_t len = yyleng -6;
                  char* content = malloc(sizeof(char) * len);
                  if (!content) {
                      logError(
                          "Impossible d'allouer la mémoire pour les "
                          "paramètres '%s' du printf ligne %d.\n",
                          yytext,
                          yylineno
                      );
                  }
                  sscanf(yytext, "printf(%s)", content);
                  yylval.str = content;
                  return PRINTF; }

{MAIN}          { return MAIN; }
{RETURN}        { return RETURN; }

int             { return TYPE_INT; }
double          { return TYPE_DOUBLE; }

{INTEGER}       { yylval.integer = atoi(yytext); 
                  return STATIC_INT; }
{DOUBLE}        { yylval.floating = atof(yytext);
                  return STATIC_DOUBLE; }

{IDENTIFICATOR} { yylval.str = malloc(sizeof(char) * strlen(yytext) +1);
                  if (!yylval.str) {
                      lexError(
                          "Impossible d'allouer la mémoire pour l'ID '%s'",
                          yytext
                      );
                  }
                  strcpy(yylval.str, yytext);
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
.	            { lexError("Caractère '%s' inconnu", yytext); }

%%

void lexError(const char* error, ...) {
    va_list arg;
    char fullError[255];

    va_start(arg, error);
    vsprintf(fullError, error, arg);
    va_end(arg);

    fflush(stdout);
    logWarning("(LEX) Ligne %d: %s\n", yylineno, fullError);
}

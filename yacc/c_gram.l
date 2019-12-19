%{
#include "y.tab.h"
void yyerror(const char *erreurMsg);
%}

%%

"include"  { yylval.str = strdup(yytext); return INCLUDE; }
"define"   { yylval.str = strdup(yytext); return DEFINE; }
"main"      { yylval.str = strdup(yytext); return MAIN; }
"return"    { yylval.str = strdup(yytext); return RETURN; }
"printf"    { yylval.str = strdup(yytext); return PRINTF; }

","         { yylval.str = strdup(yytext); return COM; }
"."         { yylval.str = strdup(yytext); return DOT; }
":"         { yylval.str = strdup(yytext); return DOT2; }
";"         { yylval.str = strdup(yytext); return SM; }
"#"         { yylval.str = strdup(yytext); return DIESE; }

"while"     { yylval.str = strdup(yytext); return WHILE; }
"do"        { yylval.str = strdup(yytext); return DO; }
"for"       { yylval.str = strdup(yytext); return FOR; }
"if"        { yylval.str = strdup(yytext); return IF; }
"else"      { yylval.str = strdup(yytext); return ELSE; }
"switch"    { yylval.str = strdup(yytext); return SWITCH; }
"case"      { yylval.str = strdup(yytext); return CASE; }
"break"     { yylval.str = strdup(yytext); return BREAK; }

"int"       { yylval.str = strdup(yytext); return INT; }
"void"      { yylval.str = strdup(yytext); return VOID; }

"=="        { yylval.str = strdup(yytext); return EQ; }
"!="        { yylval.str = strdup(yytext); return INEQ; }
"||"        { yylval.str = strdup(yytext); return OR; }
"&&"        { yylval.str = strdup(yytext); return AND; }
"<="        { yylval.str = strdup(yytext); return LOWEREG; }
">="        { yylval.str = strdup(yytext); return UPPEREG; }
"<"         { yylval.str = strdup(yytext); return LOWER; }
">"         { yylval.str = strdup(yytext); return UPPER; }

"{"         { yylval.str = strdup(yytext); return BRACEL; }
"}"         { yylval.str = strdup(yytext); return BRACER; }
"("         { yylval.str = strdup(yytext); return BRACKETL; }
")"         { yylval.str = strdup(yytext); return BRACKETR; }
"["         { yylval.str = strdup(yytext); return TABL; }
"]"         { yylval.str = strdup(yytext); return TABR; }

"="         { yylval.str = strdup(yytext); return ASSIGN; }
"+"         { yylval.str = strdup(yytext); return PLUS; }
"-"         { yylval.str = strdup(yytext); return MINUS; }
"*"         { yylval.str = strdup(yytext); return MULT; }
"/"         { yylval.str = strdup(yytext); return DIV; }
"%"         { yylval.str = strdup(yytext); return MODULO; }

<<EOF>>     return END;

\"(.*?)\" {
  yylval.str = strdup(yytext); 
  return STR;
} /* Ici on reconnait une chaîne de caractère entre "" et on la renvoie */


[a-zA-Z]+[0-9]*[a-zA-Z]* {
  yylval.str = strdup(yytext); 
  return VAR;
} /* Permet de gérer les variables et de les renvoyer */

[a-zA-Z]+[0-9]*[a-zA-Z]*\.[a-z] {
  yylval.str = strdup(yytext); 
  return EXT;
} /* Retourne extension de fichier */

[0-9]+	{
  yylval.str = strdup(yytext); 
  return ENTIER;
} /* De même pour les entiers */

[ \t\n]	;

.	yyerror("Caractere non valide");

%%

void yyerror(const char *erreurMsg) {
  fprintf(stderr, "\n Erreur '%s' sur '%s'.\n", erreurMsg, yytext);
  exit(EXIT_FAILURE);
}

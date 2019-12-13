%{
#include "y.tab.h"
void yyerror(const char *erreurMsg);
%}

%%

"include"  { return INCLUDE; }
"define"   { return DEFINE; }
"main"      { return MAIN; }
"return"    { return RETURN; }
"printf"    { return PRINTF; }

","         { return COM; }
"."         { return DOT; }
":"         { return DOT2; }
";"         { return SM; }
"#"         { return DIESE; }

"while"     { return WHILE; }
"do"        { return DO; }
"for"       { return FOR; }
"if"        { return IF; }
"else"      { return ELSE; }
"switch"    { return SWITCH; }
"case"      { return CASE; }
"break"     { return BREAK; }

"int"       { return INT; }
"void"      { return VOID; }

"=="        { return EQ; }
"!="        { return INEQ; }
"||"        { return OR; }
"&&"        { return AND; }
"<="        { return LOWEREG; }
">="        { return UPPEREG; }
"<"         { return LOWER; }
">"         { return UPPER; }

"{"         { return BRACEL; }
"}"         { return BRACER; }
"("         { return BRACKETL; }
")"         { return BRACKETR; }
"["         { return TABL; }
"]"         { return TABR; }

"="         { return ASSIGN; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MULT; }
"/"         { return DIV; }
"%"         { return MODULO; }

<<EOF>>     return END;

\"(.*?)\" {
  return STR;
} /* Ici on reconnait une chaîne de caractère entre "" et on la renvoie */


[a-zA-Z]+[0-9]*[a-zA-Z]* {
  return VAR;
} /* Permet de gérer les variables et de les renvoyer */

[a-zA-Z]+[0-9]*[a-zA-Z]*\.[a-z] {
  return EXT;
} /* Retourne extension de fichier */

[0-9]+	{
  return ENTIER;
} /* De même pour les entiers */

[ \t\n]	;

.	yyerror("Caractere non valide");

%%

void yyerror(const char *erreurMsg) {
  fprintf(stderr, "\n Erreur '%s' sur '%s'.\n", erreurMsg, yytext);
  exit(EXIT_FAILURE);
}

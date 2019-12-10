%{
//#include "y.tab.h" 
void yyerror(const char *erreurMsg);
%}

%%
\n        { //return BACK;  
}

"#include"  { //return INCLUDE; 
}
"#define"   { //return DEFINE; 
}
"main"      { //return MAIN; 
}
"return"    { //return RETOUR; 
}
"printf"    { //return PRINTF; 
}

","         { //return COM; 
}
"."         { //return DOT; 
}
":"         { //return 2DOT; 
}
";"         { //return SM; 
}

"while"     { //return WHILE; 
}
"do"        { //return DO; 
}
"for"       { //return FOR; 
}
"if"        { //return IF; 
}
"else"      { //return ELSE; 
}
"switch"    { //return SWITCH; 
}
"case"      { //return CASE; 
}
"break"     { //return break; 
}

"int"       { //return INT; 
}
"void"      { //return VOID; 
}

"=="        { //return EQ; 
}
"!="        { //return INEQ; 
}
"||"        { //return OR; 
}
"&&"        { //return AND; 
}
"<="        { //return LOWEREG; 
}
">="        { //return UPPEREG; 
}
"<"         { //return LOWER; 
}
">"         { //return UPPER; 
}

"{"         { //return BRACEL; 
}
"}"         { //return BRACER; 
}
"("         { //return BRACKETL; 
}
")"         { //return BRACKETR; 
}
"["         { //return BRACKETL; 
}
"]"         { //return BRACKETR; 
}


"="         { //return EGAL; 
}
"+"         { //return PLUS; 
}
"-"         { //return MINUS; 
}
"*"         { //return MULT; 
}
"/"         { //return DIV; 
}
"%"         { //return POURC; 
}


\"(.*?)\" {
  //yylval.var = (char*) malloc(sizeof(char)*(strlen(yytext)+1)); 
  //strcpy(yylval.var,yytext);
  //return STR;
} /* Ici on reconnait une chaîne de caractère entre "" et on la renvoie */


[a-zA-Z]+[0-9]*[a-zA-Z]* {
  //yylval.var = (char*) malloc(sizeof(char)*(strlen(yytext)+1));
  //strcpy(yylval.var,yytext);
  //return VAR;
} /* Permet de gérer les variables et de les renvoyeré */

[0-9]+	{
  //yylval.valeur = atof(yytext);
  //return ENTIER;
} /* De même pour les entiers */

[ \t]	;
'' ;
.	yyerror("Caractere non valide");

%%

void yyerror(const char *erreurMsg) {
  fprintf(stderr, "\n Erreur '%s' sur '%s'.\n", erreurMsg, yytext);
  exit(EXIT_FAILURE);
}

int main(){
	yyin=fopen("test.txt", "r");
	if(yyin == NULL){return 1;}

	
	yylex();
	//printf("%d",c);
	fclose(yyin);
return 0;
}

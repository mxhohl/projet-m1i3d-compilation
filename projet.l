%{
  #include "y.tab.h" 
void yyerror(const char *erreurMsg);
%}

%%
\n        { return BACK ;}
"return"  {return RETOUR;}
","       {return COM;}
":"       {return DOT;}
";"       {return SM;}
"int"     {return INT;}
"while"   {return WHILE;}
"do"      {return DO;}
"for"     {return FOR;}
"if"      {return IF;}
"else"    {return ELSE;}
"switch"  {return SWITCH;}
"case"    {return CASE;}
"break"   {return break;}

"=="      {return EQ;}
"!=" {return INEQ;}
"||" {return OR;}
"&&" {return AND;}
"<" {return LOWER;}
">" {return UPPER;}
"<=" {return LOWEREG;}
">=" {return UPPEREG;}

"{" {return BRACEL;}
"}" {return BRACER;}
"(" {return BRACKETL;}
")" {return BRACKETR;}


"=" {return EGALE;}

"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MULT;}
"/" {return DIV;}
"%" {return POURC;}

\"(.*?)\" {
  yylval.var = (char*) malloc(sizeof(char)*(strlen(yytext)+1));
  strcpy(yylval.var,yytext);
  return STR;
}

[-+\./*=]	{ return *yytext; }

[a-zA-Z]+ {
  yylval.var = (char*) malloc(sizeof(char)*(strlen(yytext)+1));
  strcpy(yylval.var,yytext);
  return VAR;
}

[0-9]+	{
  yylval.valeur = atof(yytext);
  return ENTIER;
}
[ \t]	;
'' ;
.	yyerror("Caractere non valide");

%%

void yyerror(const char *erreurMsg) {
  fprintf(stderr, "\n Erreur '%s' sur '%s'.\n", erreurMsg, yytext);
  exit(EXIT_FAILURE);
}
%{
    #include <stdio.h>
    #include <stdlib.h>
    int yylex();
    void yyerror(char*);
    extern FILE *yyin;
    extern FILE *yyout;
%}

%union{
  char* str;
}

%token <str> ENTIER
%token <str> VAR STR EXT
%token <str> END
%token <str> DO WHILE FOR IF ELSE BREAK SWITCH CASE RETURN 
%token <str> INCLUDE DEFINE DIESE
%token <str> UPPER UPPEREG LOWER LOWEREG EQ INEQ PLUS MINUS MULT DIV MODULO ASSIGN
%token <str> BRACEL BRACER BRACKETL BRACKETR SM COM DOT DOT2 TABL TABR
%token <str> INT VOID
%token <str> PRINTF MAIN
%token <str> AND OR

%%

axiom : header main { printf("Match\n"); return 0; }
      ;

header :
       | DIESE INCLUDE STR header { fprintf(yyout, "%s %s %s\n", $1, $2, $3); }
       | DIESE INCLUDE LOWER EXT UPPER header { fprintf(yyout, "%s %s %s %s %s\n", $1, $2, $3, $4, $5); }
       | DIESE DEFINE VAR val header { fprintf(yyout, "%s %s %s", $1, $2, $3); }
       ;

main : type MAIN BRACKETL BRACKETR BRACEL core RETURN ENTIER SM BRACER END  { fprintf(yyout, "%s %s %s %s\n %s %s %s\n %s", $2, $3, $4, $5, $7, $8, $9, $10); }
     ;

type : INT { fprintf(yyout, "%s ", $1); }
     | VOID { fprintf(yyout, "%s ", $1); }
     ;

core :
     | expression core
     ;

expression : declaration
           | iteration
           | function
           ;

declaration : type VAR SM { fprintf(yyout, "%s %s\n",$2, $3); }
            | type VAR ASSIGN val SM  { fprintf(yyout, "%s %s %s\n", $2, $3, $5); }
            | VAR ASSIGN val SM { fprintf(yyout, "%s %s %s\n", $1, $2, $4); } 
            | type VAR ASSIGN val op_binaire val SM { fprintf(yyout, "%s %s %s\n", $2, $3, $7); }
            | val op_binaire val SM { fprintf(yyout, "%s\n", $4); }
            | type tableau SM { fprintf(yyout, "%s\n", $3); } 
            | tableau ASSIGN val SM { fprintf(yyout, "%s %s\n", $2, $4); }
            | tableau ASSIGN tableau SM { fprintf(yyout, "%s %s\n", $2, $4); }
            ;

tableau : VAR TABL TABR { fprintf(yyout, "%s %s %s", $1, $2, $3); }
        | VAR TABL ENTIER TABR { fprintf(yyout, "%s %s %s %s", $1, $2, $3, $4); } 
        | VAR TABL VAR TABR { fprintf(yyout, "%s %s %s %s", $1, $2, $3, $4); }
        | VAR TABL increment TABR { fprintf(yyout, "%s %s %s", $1, $2, $4); }
        | VAR TABL operation TABR { fprintf(yyout, "%s %s %s", $1, $2, $4); }
        ;

operation : VAR op_binaire ENTIER { fprintf(yyout, "%s %s", $1, $3); }
          | VAR op_binaire VAR { fprintf(yyout, "%s %s", $1, $3); }
          | ENTIER op_binaire VAR { fprintf(yyout, "%s %s", $1, $3); }
          ;

val : VAR { fprintf(yyout, "%s", $1); }
    | ENTIER { fprintf(yyout, "%s", $1); }
    | STR { fprintf(yyout, "%s", $1); }
    ;

op_binaire : PLUS { fprintf(yyout, "%s", $1); }
           | MINUS { fprintf(yyout, "%s", $1); }
           | MULT { fprintf(yyout, "%s", $1); }
           | DIV { fprintf(yyout, "%s", $1); }
           | MODULO { fprintf(yyout, "%s", $1); }
           ;

iteration : WHILE BRACKETL condition BRACKETR BRACEL core BRACER { fprintf(yyout, "%s %s %s %s\n %s\n", $1, $2, $4, $5, $7); }
          | DO BRACEL core BRACER WHILE BRACKETL condition BRACKETR { fprintf(yyout, "%s %s\n %s %s %s %s\n", $1, $2, $4, $5, $6, $8); }
          | FOR BRACKETL condition_for BRACKETR BRACEL core BRACER { fprintf(yyout, "%s %s %s %s\n %s\n", $1, $2, $4, $5, $7); }
          | WHILE BRACKETL condition BRACKETR expression { fprintf(yyout, "%s %s %s\n", $1, $2, $4); }
          | FOR BRACKETL condition_for BRACKETR expression { fprintf(yyout, "%s %s %s\n", $1, $2, $4); }
          ;

condition : ENTIER { fprintf(yyout, "%s", $1); }
          | VAR comp val { fprintf(yyout, "%s", $1); }
          ;
        
comp : UPPER { fprintf(yyout, "%s", $1); }
     | LOWER { fprintf(yyout, "%s", $1); }
     | LOWEREG { fprintf(yyout, "%s", $1); }
     | UPPEREG { fprintf(yyout, "%s", $1); }
     | EQ { fprintf(yyout, "%s", $1); }
     | INEQ { fprintf(yyout, "%s", $1); }
     ;

condition_for : SM SM { fprintf(yyout, "%s %s", $1, $2); }
              | declaration condition SM increment { fprintf(yyout, "%s", $3); }
              ;

increment : VAR op_inc { fprintf(yyout, "%s", $1); }
          | op_inc VAR { fprintf(yyout, "%s", $2); }
          ;

op_inc : PLUS PLUS { fprintf(yyout, "%s %s", $1, $2); }
       | MINUS MINUS { fprintf(yyout, "%s %s", $1, $2); }
       ;

function : PRINTF BRACKETL STR BRACKETR SM { fprintf(yyout, "%s %s %s %s %s\n", $1, $2, $3, $4, $5); }
         | PRINTF BRACKETL STR COM variable BRACKETR SM { fprintf(yyout, "%s %s %s %s %s %s\n", $1, $2, $3, $4, $6, $7); }
         ;

variable : tableau
         | VAR { fprintf(yyout, "%s", $1); }
         | tableau COM variable { fprintf(yyout, "%s", $2); }
         | VAR COM variable { fprintf(yyout, "%s %s", $1, $2); }
         ;

%%

int main()
{
    yyin = fopen("test.c", "r");
    if(yyin == NULL)
    {
        fprintf(stderr, "erreur fopen input\n");
        exit(1);
    }

    yyout = fopen("output.c", "w+");
    if(yyout == NULL)
    {
        fprintf(stderr, "erreur fopen output\n");
        exit(1);
    }
    yyparse();
    yylex();
    fclose(yyin);
    fclose(yyout);
    return 0;
}

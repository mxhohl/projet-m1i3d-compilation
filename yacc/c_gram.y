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

header : { fprintf(yyout, "#include \"sources.h\"\n\n"); }
       | DIESE INCLUDE STR { fprintf(yyout, "%s%s %s\n", $1, $2, $3); } header
       | DIESE INCLUDE LOWER EXT UPPER { fprintf(yyout, "%s%s %s%s%s\n", $1, $2, $3, $4, $5); } header
       | DIESE DEFINE VAR { fprintf(yyout, "%s%s %s ", $1, $2, $3); } val { fprintf(yyout, "\n"); } header
       ;

main : type MAIN BRACKETL BRACKETR BRACEL { fprintf(yyout, "%s%s%s%s\n", $2, $3, $4, $5); } core RETURN ENTIER SM BRACER END { fprintf(yyout, "%s %s%s\n %s", $8, $9, $10, $11); }
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
            | type VAR ASSIGN { fprintf(yyout, "%s %s ", $2, $3); } ss_dec1
            | VAR ASSIGN { fprintf(yyout, "%s %s", $1, $2); } val SM { fprintf(yyout, "%s\n", $5); } 
            | val op_binaire val SM  { fprintf(yyout, "%s\n", $4); } 
            | type tableau SM { fprintf(yyout, "%s\n", $3); } 
            | tableau ASSIGN { fprintf(yyout, "%s", $2); } ss_dec1
            ;

ss_dec1 : val SM { fprintf(yyout, "%s\n", $2); }
        | val op_binaire val SM { fprintf(yyout, "%s\n", $4); }
        | tableau SM { fprintf(yyout, "%s\n", $2); }
        ;

tableau : VAR TABL TABR { fprintf(yyout, "%s%s%s", $1, $2, $3); }
        | VAR TABL ENTIER TABR { fprintf(yyout, "%s%s%s%s", $1, $2, $3, $4); } 
        | VAR TABL VAR TABR { fprintf(yyout, "%s%s%s%s", $1, $2, $3, $4); }
        | VAR TABL { fprintf(yyout, "%s%s ", $1, $2); } ss_tab1
        ;

ss_tab1 : increment TABR { fprintf(yyout, "%s", $2); }
        | operation TABR { fprintf(yyout, "%s", $2); }
        ;

operation : VAR { fprintf(yyout, "%s ", $1); } ss_ope
          | ENTIER { fprintf(yyout, "%s ", $1); } ss_ope
          ;

ss_ope : op_binaire ENTIER { fprintf(yyout, "%s ", $2); }
       | op_binaire VAR { fprintf(yyout, "%s ", $2); }
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

iteration : WHILE BRACKETL { fprintf(yyout, "%s%s ", $1, $2); } ss_ite1
          | DO BRACEL { fprintf(yyout, "%s %s\n", $1, $2); } core BRACER WHILE BRACKETL { fprintf(yyout, "%s %s%s\n", $5, $6, $7); } condition BRACKETR SM { fprintf(yyout, "%s%s\n", $10, $11); }
          | FOR BRACKETL { fprintf(yyout, "%s%s", $1, $2); } ss_ite2
          ;

ss_ite1 : condition BRACKETR BRACEL { fprintf(yyout, "%s %s\n\t", $2, $3); } core BRACER { fprintf(yyout, "%s\n", $6); }
        | condition BRACKETR { fprintf(yyout, "%s\n\t", $2); } expression
        ;

ss_ite2 : condition_for BRACKETR BRACEL { fprintf(yyout, "%s %s\n\t", $2, $3); } core BRACER { fprintf(yyout, "%s\n", $6); }
        | condition_for BRACKETR { fprintf(yyout, "%s\n\t", $2); } expression
        ;

condition : ENTIER { fprintf(yyout, "%s", $1); }
          | VAR { fprintf(yyout, "%s", $1); } comp val
          ;
        
comp : UPPER { fprintf(yyout, "%s", $1); }
     | LOWER { fprintf(yyout, "%s", $1); }
     | LOWEREG { fprintf(yyout, "%s", $1); }
     | UPPEREG { fprintf(yyout, "%s", $1); }
     | EQ { fprintf(yyout, "%s", $1); }
     | INEQ { fprintf(yyout, "%s", $1); }
     ;

condition_for : SM SM { fprintf(yyout, "%s %s", $1, $2); }
              | declaration condition SM { fprintf(yyout, "%s", $3); } increment
              ;

increment : VAR { fprintf(yyout, "%s", $1); } op_inc
          | op_inc VAR { fprintf(yyout, "%s", $2); }
          ;

op_inc : PLUS PLUS { fprintf(yyout, "%s%s", $1, $2); }
       | MINUS MINUS { fprintf(yyout, "%s%s", $1, $2); }
       ;

function : PRINTF BRACKETL STR BRACKETR SM { fprintf(yyout, "%s%s %s %s%s\n", $1, $2, $3, $4, $5); }
         | PRINTF BRACKETL STR COM { fprintf(yyout, "%s%s %s %s ", $1, $2, $3, $4); } variable BRACKETR SM { fprintf(yyout, "%s%s\n", $7, $8); }
         ;

variable : tableau
         | VAR { fprintf(yyout, "%s", $1); }
         | tableau COM { fprintf(yyout, "%s", $2); } variable
         | VAR COM { fprintf(yyout, "%s %s", $1, $2); } variable
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

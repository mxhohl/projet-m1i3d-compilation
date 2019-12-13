%{
    #include <stdio.h>
    int yylex();
    void yyerror(char*);
    FILE *yyin;
%}

%token VAR ENTIER STR EXT
%token END
%token DO WHILE FOR IF ELSE BREAK SWITCH CASE RETURN 
%token INCLUDE DEFINE DIESE
%token UPPER UPPEREG LOWER LOWEREG EQ INEQ PLUS MINUS MULT DIV MODULO ASSIGN
%token BRACEL BRACER BRACKETL BRACKETR SM COM DOT DOT2 TABL TABR
%token INT VOID
%token PRINTF MAIN
%token AND OR

%%

axiom : header main { printf("Match\n"); return 0; }
      ;

header :
       | DIESE INCLUDE STR header
       | DIESE INCLUDE LOWER EXT UPPER header
       | DIESE DEFINE VAR val header
       ;

main : type MAIN BRACKETL BRACKETR BRACEL core RETURN ENTIER SM BRACER END
     ;

type : INT
     | VOID
     ;

core :
     | expression core
     ;

expression : declaration { printf("declaration\n"); }
           | iteration { printf("iteration\n"); }
           | function { printf("function\n"); }
           ;

declaration : type VAR SM
            | type VAR ASSIGN val SM
            | VAR ASSIGN val SM
            | type VAR ASSIGN val op_binaire val SM
            | val op_binaire val SM
            | type tableau SM
            | tableau ASSIGN val SM
            | tableau ASSIGN tableau SM
            ;

tableau : VAR TABL TABR
        | VAR TABL ENTIER TABR
        | VAR TABL VAR TABR
        | VAR TABL increment TABR
        | VAR TABL operation TABR
        ;

operation : VAR op_binaire ENTIER
          | VAR op_binaire VAR
          | ENTIER op_binaire VAR
          ;

val : VAR
    | ENTIER
    | STR
    ;

op_binaire : PLUS
           | MINUS
           | MULT
           | DIV
           | MODULO
           ;

iteration : WHILE BRACKETL condition BRACKETR BRACEL core BRACER
          | DO BRACEL core BRACER WHILE BRACKETL condition BRACKETR
          | FOR BRACKETL condition_for BRACKETR BRACEL core BRACER
          | WHILE BRACKETL condition BRACKETR expression
          | FOR BRACKETL condition_for BRACKETR expression
          ;

condition : ENTIER
          | VAR comp val
          ;
        
comp : UPPER
     | LOWER
     | LOWEREG
     | UPPEREG
     | EQ
     | INEQ
     ;

condition_for : SM SM
              | declaration condition SM increment
              ;

increment : VAR op_inc
          | op_inc VAR
          ;

op_inc : PLUS PLUS
       | MINUS MINUS
       ;

function : PRINTF BRACKETL STR BRACKETR SM
         | PRINTF BRACKETL STR COM variable BRACKETR SM
         ;

variable : tableau
         | VAR
         | tableau COM variable
         | VAR COM variable
         ;

%%

int main()
{
    yyin = fopen("test.c", "r");
    if(yyin == NULL)
    {
        fprintf(stderr, "erreur fopen\n");
        return 1;
    }
    yyparse();
    yylex();
    fclose(yyin);
    return 0;
}

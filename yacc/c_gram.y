%{
    #include <stdio.h>
    int yylex();
    void yyerror(char*);
    FILE *yyin;
%}

%token VAR ENTIER STR
%token BACK
%token DO WHILE FOR IF ELSE BREAK SWITCH CASE RETURN MAIN 
%token INCLUDE DEFINE
%token UPPER UPPEREG LOWER LOWEREG EQ INEQ PLUS MINUS MULT DIV MODULO EGAL
%token BRACEL BRACER BRACKETL BRACKETR SM COM DOT DOT2 TABL TABR
%token INT VOID
%token PRINTF
%token AND OR

%%

axiom : main { printf("Match\n"); return 0; }
      | header main { printf("Match\n"); return 0; }
      ;

header : BACK
       | INCLUDE STR BACK header
       | INCLUDE LOWER VAR UPPER BACK header { printf("include <>\n"); }
       | DEFINE VAR val BACK header { printf("define\n"); }
       ;

main : type MAIN BRACKETL BRACKETR BRACEL core BRACER { printf("on est dans le main\n"); }
     ;

type : INT
     | VOID
     ;

core : expression core
     | RETURN ENTIER SM { printf("return 0;\n"); }
     ;

expression : declaration
           | iteration
           ;

declaration : type VAR SM
            | type VAR EGAL val SM
            | type VAR EGAL val OP_BINAIRE val SM
            | val OP_BINAIRE val SM
            | tableau SM
            | tableau EGAL val
            | tableau EGAL tableau
            ;

tableau : VAR TABL TABR
        | VAR TABL ENTIER TABR
        | VAR TABL VAR TABR
        | VAR TABL increment TABR
        ;

val : VAR
    | ENTIER
    | STR
    ;

OP_BINAIRE : PLUS
           | MINUS
           | MULT
           | DIV
           | MODULO
           ;

iteration : WHILE BRACKETL condition BRACKETR BRACEL expression BRACER
          | DO BRACEL expression BRACER WHILE BRACKETL condition BRACKETR
          | FOR BRACKETL condition_for BRACKETR BRACEL expression BRACER
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
              | declaration condition increment
              ;

increment : VAR op_inc
          | op_inc VAR
          ;

op_inc : "++"
       | "--"
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

    yylex();
    fclose(yyin);
    return 0;
}
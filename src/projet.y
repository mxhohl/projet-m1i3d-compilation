%{
    #include <stdio.h>
    int yylex();
    void yyerror(char*);
    extern FILE *yyin;
%}

%token VAR ENTIER STR
//%token BACK
%token DO WHILE FOR IF ELSE BREAK SWITCH CASE RETURN MAIN 
%token INCLUDE DEFINE
%token UPPER UPPEREG LOWER LOWEREG EQ INEQ PLUS MINUS MULT DIV MODULO EGAL
%token BRACEL BRACER BRACKETL BRACKETR SM COM DOT DOT2 TABL TABR
%token INT VOID
%token PRINTF
%token AND OR

%left PLUS MINUS MULT DIV MODULO
%right EGAL

%%

axiom : main { printf("Match\n"); return 0; }
      | header main { printf("Match\n"); return 0; }
      ;

header :
       | INCLUDE STR header
       | INCLUDE LOWER VAR UPPER header { printf("include <>\n"); }
       | DEFINE VAR val header { printf("define\n"); }
       ;

main : type MAIN BRACKETL BRACKETR BRACEL core RETURN ENTIER SM BRACER { printf("on est dans le main\n"); }
     ;

type : INT
     | VOID
     ;

core : 
     | expression core
     ;

expression : declaration
           | iteration
           ;

declaration : type VAR declaration2 SM
            | type VAR EGAL val SM
			| type tableau declaration2 SM
            | VAR EGAL val SM
            | type VAR EGAL val op_binaire val SM
            | val op_binaire val SM
            | tableau SM
            | tableau EGAL val SM
            | tableau EGAL tableau SM
            ;

declaration2 :
			 | COM VAR declaration2
			 | COM tableau declaration2
			 ;

tableau : VAR TABL TABR
        | VAR TABL ENTIER TABR
        | VAR TABL VAR TABR
        | VAR TABL increment TABR
        ;

val : operation
	| STR
	;

operation : operation op_binaire operation
		  | VAR
		  | ENTIER
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

%%

int main()
{
    yyin = fopen("test2.c", "r");
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

%{

#include <stdio.h>
#include <stdlib.h>

#include "ast.h"


extern int yylex();
extern FILE* yyin;
extern int yylineno;


void yyerror(const char*);

%}

%define parse.error verbose

%union {
    int integer;
    double floating;
    char* str;
}

%token              EOFILE

%token              TYPE_INT
%token              TYPE_DOUBLE

%token <integer>    STATIC_INT
%token <floating>   STATIC_DOUBLE

%token <str>        ID

%token              OP_PLUS
%token              OP_MINUS
%token              OP_MULTIPLY
%token              OP_DIVIDE
%token              OP_INCREMENT
%token              OP_DECREMENT

%token              OP_EQ
%token              OP_NEQ
%token              OP_AND
%token              OP_OR
%token              OP_LOWER
%token              OP_LOWER_EQ
%token              OP_GREATER
%token              OP_GREATER_EQ
%token              OP_NOT

%token              MAIN

%token              IF
%token              ELSE
%token              WHILE
%token              FOR

%token <str>        PRINTF

%token              SEMICOLON
%token              COMMA
%token              EQUAL
%token              LPARENTHESIS
%token              RPARENTHESIS
%token              LBRACE
%token              RBRACE
%token              LBRACKET
%token              RBRACKET

%start axiom

%%


/****************************************/
/*****            AXIOM             *****/
/****************************************/

axiom   : file  { puts("axiom"); return 0; }
        ;



/****************************************/
/*****             FILE             *****/
/****************************************/

file    : main EOFILE   { puts("file"); }

main    : MAIN LBRACE instruction_list RBRACE { puts("main"); }


/****************************************/
/*****         INSTRUCTIONS         *****/
/****************************************/

instruction_block   : instruction
                    | LBRACE instruction_list RBRACE
                    ;

instruction_list    : instruction instruction_list  { puts("instruction_list 1"); }
                    | /* epsilon */                 { puts("instruction_list 2"); }
                    ;

instruction     : PRINTF SEMICOLON              { printf("printf(%s)\n", $1); }
                | declaration_list SEMICOLON    { puts("instruction 1"); }
                | assignation_list SEMICOLON    { puts("instruction 2"); }
                | control_flow                  { puts("instruction 3"); }
                | expression SEMICOLON          { puts("instruction 4"); }
                | SEMICOLON                     { puts("instruction 5"); }
                ;


/****************************************/
/*****    STRUCTURES DE CONTROLE    *****/
/****************************************/

control_flow    : for
                | while
                | ifelse
                ;

for : FOR LPARENTHESIS 
        for_init SEMICOLON 
        for_expr SEMICOLON 
        for_expr
      RPARENTHESIS instruction_block    { puts("for"); }

for_init    : declaration_list
            | assignation_list
            ;

for_expr    : expression    { puts("for_expr 1"); }
            | /* epsilon */ { puts("for_expr 2"); }
            ;

while   : WHILE LPARENTHESIS expression RPARENTHESIS instruction_block  { puts("while"); }
        ;

ifelse  : if
        | if ELSE instruction_block

if  : IF LPARENTHESIS expression RPARENTHESIS instruction_block { puts("if"); }
    ;


/****************************************/
/*****         DECLARATIONS         *****/
/****************************************/

declaration_list    : type declaration_list2    { puts("declaration_list"); }
                    ;

declaration_list2   : declaration COMMA declaration_list2   { puts("declaration_list2 1"); }
                    | declaration                           { puts("declaration_list2 2"); }
                    ;

declaration : declarator                    { puts("declaration 1"); }
            | declarator EQUAL initializer  { puts("declaration 2"); }
            ;

declarator  : ID
            | declarator LBRACKET RBRACKET
            | declarator LBRACKET expression RBRACKET
            ;

initializer : expression
            ;


/****************************************/
/*****         ASSIGNATIONS         *****/
/****************************************/

assignation_list    : assignation COMMA assignation_list    { puts("assignation_list 1"); }
                    | assignation                           { puts("assignation_list 2"); }
                    ;

assignation :   ID EQUAL expression { puts("assignation"); }
            ;


/****************************************/
/*****          EXPRESSIONS         *****/
/****************************************/
/* Ne fonctionne pas (sans doutes à cause de 'assignation_list')
expression  : expression COMMA or_expr
            | or_expr
            ;
*/
expression  : or_expr
            ;

or_expr : and_expr
        | or_expr OP_OR and_expr
        ;

and_expr    : equality_expr
            | and_expr OP_AND equality_expr
            ;

equality_expr   : comparison_expr
                | equality_expr OP_EQ comparison_expr
                | equality_expr OP_NEQ comparison_expr
                ;

comparison_expr : addition_expr
                | comparison_expr OP_LOWER addition_expr
                | comparison_expr OP_LOWER_EQ addition_expr
                | comparison_expr OP_GREATER addition_expr
                | comparison_expr OP_GREATER_EQ addition_expr
                ;

addition_expr   : multiplication_expr
                | addition_expr OP_PLUS multiplication_expr
                | addition_expr OP_MINUS multiplication_expr
                ;

multiplication_expr : prefix_op_expr
                    | multiplication_expr OP_MULTIPLY prefix_op_expr
                    | multiplication_expr OP_DIVIDE prefix_op_expr
                    ;

prefix_op_expr  : postfix_op_expr
                | OP_PLUS prefix_op_expr
                | OP_MINUS prefix_op_expr
                | OP_INCREMENT prefix_op_expr
                | OP_DECREMENT prefix_op_expr
                | OP_NOT prefix_op_expr
                ;

postfix_op_expr : primary_expr
                | postfix_op_expr LBRACKET expression RBRACKET
                | postfix_op_expr LPARENTHESIS call_arguments RPARENTHESIS
                | postfix_op_expr LPARENTHESIS RPARENTHESIS
                | postfix_op_expr OP_INCREMENT
                | postfix_op_expr OP_DECREMENT
                ;

call_arguments  : expression
                | call_arguments COMMA expression
                ;


primary_expr    : ID
                | static_value
                | LPARENTHESIS expression RPARENTHESIS
                ;


/****************************************/
/*****            OTHERS            *****/
/****************************************/

type    : TYPE_INT      { puts("TYPE_INT"); }
        | TYPE_DOUBLE   { puts("TYPE_DOUBLE"); }
        ;

static_value    : STATIC_INT    { puts("STATIC_INT"); }
                | STATIC_DOUBLE { puts("STATIC_DOUBLE"); }
                ;

%%

void yyerror(const char* error) {
    fflush(stdout);
    fprintf(
        stderr, 
        "\n\033[1;31mErreur Yacc : '%s' à la ligne %d\033[0m\n", 
        error,
        yylineno
    );
}

/* TODO: nouveaux arguments: table des symboles */
ASTNode* parse_file(FILE* inFile) {
    yyin = inFile;
    yyparse();

    return (ASTNode*)1;
}

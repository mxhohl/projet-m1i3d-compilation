%{

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "logging.h"
#include "ast.h"
#include "symbol_table.h"


extern int yylex();
extern FILE* yyin;
extern int yylineno;


int symbolShouldExist(const char*);
int symbolShouldntExist(const char*);

void yyerror(const char*, ...);


SymbolTable* st;
int errorOccured = 0;
ASTNode* generatedAST = NULL;

%}


// %define parse.error verbose


%union {
    int integer;
    double floating;
    char* str;
    struct s_astNode* ast;
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


%type <ast>         file
%type <ast>         main

%type <ast>         instruction_block
%type <ast>         instruction_list
%type <ast>         instruction

%type <ast>         control_flow
%type <ast>         for
%type <ast>         for_init
%type <ast>         for_expr
%type <ast>         while
%type <ast>         ifelse
%type <ast>         if

%type <ast>         declaration_list
%type <ast>         declaration_list2
%type <ast>         declaration

%type <ast>         assignation_list
%type <ast>         assignation

%type <ast>         expression
%type <ast>         or_expr
%type <ast>         and_expr
%type <ast>         equality_expr
%type <ast>         comparison_expr
%type <ast>         addition_expr
%type <ast>         multiplication_expr
%type <ast>         prefix_op_expr
%type <ast>         postfix_op_expr
%type <ast>         call_arguments
%type <ast>         primary_expr

%type <ast>         static_value


%nonassoc   NO_ELSE
%nonassoc   ELSE


%start axiom

%%


/****************************************/
/*****            AXIOM             *****/
/****************************************/

axiom   : file
            {
                generatedAST = $1;
                return 0;
            }
        ;



/****************************************/
/*****             FILE             *****/
/****************************************/

file    : main EOFILE
            {
                $$ = $1;
            }

main    : MAIN LBRACE instruction_list RBRACE
            {
                $$ = $3;
            }


/****************************************/
/*****         INSTRUCTIONS         *****/
/****************************************/

instruction_block   : instruction
                        {
                            $$ = $1;
                        }
                    | LBRACE instruction_list RBRACE
                        {
                            $$ = $2;
                        }
                    ;

instruction_list    : instruction instruction_list
                        {
                            $$ = astCreateInstructionList($1, $2);
                        }
                    | /* epsilon */
                        {
                            $$ = NULL;
                        }
                    ;

instruction     : PRINTF SEMICOLON
                    {
                        $$ = astCreatePrintf($1);
                    }
                | declaration_list SEMICOLON
                    {
                        $$ = $1;
                    }
                | assignation_list SEMICOLON
                    {
                        $$ = $1;
                    }
                | control_flow
                    {
                        $$ = $1;
                    }
                | expression SEMICOLON
                    {
                        $$ = $1;
                    }
                | SEMICOLON
                    {
                        $$ = NULL;
                    }
                ;


/****************************************/
/*****    STRUCTURES DE CONTROLE    *****/
/****************************************/

control_flow    : for
                    {
                        $$ = $1;
                    }
                | while
                    {
                        $$ = $1;
                    }
                | ifelse
                    {
                        $$ = $1;
                    }
                ;

for : FOR LPARENTHESIS 
        for_init SEMICOLON 
        for_expr SEMICOLON 
        for_expr
      RPARENTHESIS instruction_block
            {
                $$ = astCreateForLoop($3, $5, $7, $9);
            }

for_init    : declaration_list
                {
                    $$ = $1;
                }
            | assignation_list
                {
                    $$ = $1;
                }
            ;

for_expr    : expression
                {
                    $$ = $1;
                }
            | /* epsilon */
                {
                    $$ = NULL;
                }
            ;

while   : WHILE LPARENTHESIS expression RPARENTHESIS instruction_block
            {
                $$ = astCreateLoop($3, $5);
            }
        ;

ifelse  : if %prec NO_ELSE
            {
                $$ = $1;
            }
        | if ELSE instruction_block
            {
                ASTNode* ifNode = $1;
                ifNode->branch.elseBody = $3;
                $$ = ifNode;
            }

if  : IF LPARENTHESIS expression RPARENTHESIS instruction_block
        {
            $$ = astCreateBranch($3, $5, NULL);
        }
    ;


/****************************************/
/*****         DECLARATIONS         *****/
/****************************************/

declaration_list    : TYPE_INT declaration_list2
                        {
                            ASTNode* node = $2;
                            stSetUnknownDataTypes(st, DT_INT);
                            $$ = node;
                        }
                    | TYPE_DOUBLE declaration_list2
                        {
                            ASTNode* node = $2;
                            stSetUnknownDataTypes(st, DT_DOUBLE);
                            $$ = node;
                        }
                    ;

declaration_list2   : declaration COMMA declaration_list2
                        {
                            $$ = astCreateInstructionList($1, $3);
                        }
                    | declaration
                        {
                            $$ = $1;
                        }
                    ;

declaration : ID 
                {
                    symbolShouldntExist($1);
                    stAddVariableSymbol(st, $1, DT_UNKNOWN);
                    $$ = astCreateVarDeclaration($1);
                }
            | ID EQUAL expression
                {
                    symbolShouldntExist($1);
                    stAddVariableSymbol(st, $1, DT_UNKNOWN);
                    $$ = astCreateInstructionList(
                        astCreateVarDeclaration($1),
                        astCreateVarAssignment($1, $3)
                    );
                }
            | ID LBRACKET STATIC_INT RBRACKET
                {
                    symbolShouldntExist($1);
                    stAddArraySymbol(st, $1, DT_UNKNOWN, $3);
                    $$ = astCreateArrayDeclaration($1, $3);
                }
            ;


/****************************************/
/*****         ASSIGNATIONS         *****/
/****************************************/

assignation_list    : assignation COMMA assignation_list
                        {
                            $$ = astCreateInstructionList($1, $3);
                        }
                    | assignation
                        {
                            $$ = $1;
                        }
                    ;

assignation : ID EQUAL expression 
                { 
                    symbolShouldExist($1);
                    $$ = astCreateVarAssignment($1, $3);
                }
            | ID LBRACKET expression RBRACKET EQUAL expression
                {
                    $$ = astCreateArrayAssignment($1, $3, $6); 
                }
            ;


/****************************************/
/*****          EXPRESSIONS         *****/
/****************************************/

expression  : or_expr
                {
                    $$ = $1;
                }
            ;

or_expr : and_expr
            {
                $$ = $1;
            }
        | or_expr OP_OR and_expr
            {
                $$ = astCreateOperatorOr($1, $3);
            }
        ;

and_expr    : equality_expr
                {
                    $$ = $1;
                }
            | and_expr OP_AND equality_expr
                {
                    $$ = astCreateOperatorAnd($1, $3);
                }
            ;

equality_expr   : comparison_expr
                    {
                        $$ = $1;
                    }
                | equality_expr OP_EQ comparison_expr
                    {
                        $$ = astCreateOperatorEqual($1, $3);
                    }
                | equality_expr OP_NEQ comparison_expr
                    {
                        $$ = astCreateOperatorNotEqual($1, $3);
                    }
                ;

comparison_expr : addition_expr
                    {
                        $$ = $1;
                    }
                | comparison_expr OP_LOWER addition_expr
                    {
                        $$ = astCreateOperatorLower($1, $3);
                    }
                | comparison_expr OP_LOWER_EQ addition_expr
                    {
                        $$ = astCreateOperatorLowerEqual($1, $3);
                    }
                | comparison_expr OP_GREATER addition_expr
                    {
                        $$ = astCreateOperatorGreater($1, $3);
                    }
                | comparison_expr OP_GREATER_EQ addition_expr
                    {
                        $$ = astCreateOperatorGreaterEqual($1, $3);
                    }
                ;

addition_expr   : multiplication_expr
                    {
                        $$ = $1;
                    }
                | addition_expr OP_PLUS multiplication_expr
                    {
                        $$ = astCreateOperatorAdd($1, $3);
                    }
                | addition_expr OP_MINUS multiplication_expr
                    {
                        $$ = astCreateOperatorSubstract($1, $3);
                    }
                ;

multiplication_expr : prefix_op_expr
                        {
                            $$ = $1;
                        }
                    | multiplication_expr OP_MULTIPLY prefix_op_expr
                        {
                            $$ = astCreateOperatorMultiply($1, $3);
                        }
                    | multiplication_expr OP_DIVIDE prefix_op_expr
                        {
                            $$ = astCreateOperatorDivide($1, $3);
                        }
                    ;

prefix_op_expr  : postfix_op_expr
                    {
                        $$ = $1;
                    }
                | OP_PLUS prefix_op_expr
                    {
                        $$ = astCreateOperatorPlus($2);
                    }
                | OP_MINUS prefix_op_expr
                    {
                        $$ = astCreateOperatorMinus($2);
                    }
                | OP_INCREMENT prefix_op_expr
                    {
                        $$ = astCreateOperatorPrefIncrement($2);
                    }
                | OP_DECREMENT prefix_op_expr
                    {
                        $$ = astCreateOperatorPrefDecrement($2);
                    }
                | OP_NOT prefix_op_expr
                    {
                        $$ = astCreateOperatorNot($2);
                    }
                ;

postfix_op_expr : primary_expr
                    {
                        $$ = $1;
                    }
                | postfix_op_expr LBRACKET expression RBRACKET
                    {
                        $$ = astCreateOperatorArrayAccess($1, $3);
                    }
                | postfix_op_expr LPARENTHESIS call_arguments RPARENTHESIS
                    {
                        $$ = astCreateOperatorCall($1, $3);
                    }
                | postfix_op_expr LPARENTHESIS RPARENTHESIS
                    {
                        $$ = astCreateOperatorCall($1, NULL);
                    }
                | postfix_op_expr OP_INCREMENT
                    {
                        $$ = astCreateOperatorPostIncrement($1);
                    }
                | postfix_op_expr OP_DECREMENT
                    {
                        $$ = astCreateOperatorPostDecrement($1);
                    }
                ;

call_arguments  : expression
                    {
                        $$ = astCreateInstructionList($1, NULL);
                    }
                | call_arguments COMMA expression
                    {
                        $$ = astCreateInstructionList($1, $3);
                    }
                ;


primary_expr    : ID
                    {
                        symbolShouldExist($1);
                        $$ = astCreateVariableRef($1);
                    }
                | static_value
                    {
                        $$ = $1;
                    }
                | LPARENTHESIS expression RPARENTHESIS  
                    { 
                        $$ = $2; 
                    }
                ;


/****************************************/
/*****        STATIC VALUES         *****/
/****************************************/

static_value    : STATIC_INT    
                    { 
                        stAddStaticInt(st, $1);
                        $$ = astCreateStaticInt($1); 
                    }
                | STATIC_DOUBLE 
                    {
                        stAddStaticDouble(st, $1);
                        $$ = astCreateStaticDouble($1); 
                    }
                ;

%%

int symbolShouldExist(const char* name) {
    if (!stSymbolExist(st, name)) {
        yyerror("La variable '%s' n'est pas définis.", name);
        return 0;
    }
    return 1;
}

int symbolShouldntExist(const char* name) {
    if (stSymbolExist(st, name)) {
        yyerror("La variable '%s' est déjà définis.", name);
        return 0;
    }
    return 1;
}

void yyerror(const char* error, ...) {
    va_list arg;
    char fullError[255];

    va_start(arg, error);
    vsprintf(fullError, error, arg);
    va_end(arg);

    fflush(stdout);
    logError("(YACC) Ligne %d: %s\n", yylineno, fullError);

    errorOccured = 1;
}

ASTNode* parse_file(FILE* inFile, SymbolTable* symbolTable) {
    yyin = inFile;
    st = symbolTable;

    yyparse();

    if (!errorOccured) {
        return generatedAST;
    } else {
        astFree(generatedAST);
        return NULL;
    }
}

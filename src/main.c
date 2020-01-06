#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cl_parameters.h"
#include "ast.h"
#include "symbol_table.h"

extern ASTNode* parse_file(FILE*);

void doJob(clParameters* parameters);

int main(int argc, char** argv) {
    
    clParameters* parameters = clGetParameters(argc, argv);

    printf(
        "Print AST: %s\n"
        "Print TOS: %s\n"
        "In       : %s\n"
        "Out      : %s\n",
        parameters->printAst ? "true" : "false",
        parameters->printTos ? "true" : "false",
        parameters->inFile,
        parameters->outFile
    );

    doJob(parameters);

    clFree(parameters);

    return 0;
}

void doJob(clParameters* parameters) {

    FILE* inFile = fopen(parameters->inFile, "r");
    if (!inFile) {
        fprintf(stderr, "Unable to open file %s\n", parameters->inFile);
        exit(1);
    }

    SymbolTable* st = stCreate();

    ASTNode* ast = parse_file(inFile);

    if (!ast) {
        puts("Une erreur est survenue. Arret.");
        exit(10);
    }

    if (parameters->printTos) {
        stPrint(st, stdout);
    }

    /* TODO: print AST if parameter */

    /* TODO: replace paterns with functions calls */

    /* TODO: print AST if parameter */

    stFree(st);
}

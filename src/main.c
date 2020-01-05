#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cl_parameters.h"
#include "ast.h"
#include "symbol_table.h"

extern ASTNode* parse_file(FILE*);

void doJob();

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

    /* doJob(); */

    clFree(parameters);

    return 0;
}

void doJob() {
    const char* const filePath = "test.c";

    FILE* inFile = fopen(filePath, "r");
    if (!inFile) {
        fprintf(stderr, "Unable to open file %s\n", filePath);
        exit(1);
    }

    SymbolTable* st = stCreate();

    puts("Parsing...");

    ASTNode* ast = parse_file(inFile);

    if (!ast) {
        puts("Une erreur est survenue. Arret.");
        exit(10);
    }

    puts("Done");

    stPrint(st, stdout);

    stFree(st);
}

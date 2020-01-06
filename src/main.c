#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "logging.h"
#include "cl_parameters.h"
#include "ast.h"
#include "symbol_table.h"

extern ASTNode* parse_file(FILE*, SymbolTable*);

int doJob(clParameters* parameters);

int main(int argc, char** argv) {
    clParameters* parameters = clGetParameters(argc, argv);

    int result = doJob(parameters);

    clFree(parameters);

    return result;
}

int doJob(clParameters* parameters) {

    FILE* inFile = fopen(parameters->inFile, "r");
    if (!inFile) {
        logError("Unable to open file %s\n", parameters->inFile);
        exit(1);
    }

    SymbolTable* st = stCreate();
    ASTNode* ast;

    ast = parse_file(inFile, st);

    if (!ast) {
        logError("Une erreur est survenue. Arret.\n");

        fclose(inFile);
        stFree(st);
        exit(10);
    }

    if (parameters->printTos) {
        stPrint(st, stdout);
    }

    if (parameters->printAst) {
        astPrint(ast, stdout);
    }

    /* TODO: replace paterns with functions calls */

/*  TODO: décommenter une fois l'étape précédente éffectuée
    if (parameters->printAst) {
        astPrint(ast, stdout);
    }
*/
    fclose(inFile);
    astFree(ast);
    stFree(st);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "logging.h"
#include "cl_parameters.h"
#include "ast.h"
#include "symbol_table.h"
#include "blas.h"
#include "c_generator.h"

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
        logError("Impossible d'ouvrir le fichier %s\n", parameters->inFile);
        exit(1);
    }

    FILE* outFile = fopen(parameters->outFile, "w");
    if (!outFile) {
        logError("Impossible d'ouvrir le fichier %s\n", parameters->outFile);
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
        fprintf(stdout, "AST avant replacement des BLAS\n");
        astPrint(ast, stdout);
    }

    size_t blasCount = 0;
    BLAS** blas = loadBlas(&blasCount);

    size_t replacedCount = replaceBlasInAst(blas, blasCount, &ast);
    logMessage("%lu BLAS remplacés dans l'AST.\n", replacedCount);

    if (parameters->printAst) {
        fprintf(stdout, "AST après replacement des BLAS\n");
        astPrint(ast, stdout);
    }

    astToC(outFile, ast, st);

    fclose(inFile);
    fclose(outFile);
    astFree(ast);
    stFree(st);
    freeAllBlas(blas, blasCount);

    return 0;
}

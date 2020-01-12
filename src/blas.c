#include "blas.h"

#include <stdlib.h>
#include <stdio.h>

BLAS* blasCreate(char* name, ASTNode* root) {
    BLAS* blas = malloc(sizeof(struct s_blas));
    blas->name = name;
    blas->root = root;

    return blas;
}

void blasFree(BLAS* blas) {
    free(blas);
}

ASTNode** getBlasInAst(BLAS* blas, ASTNode* ast) {
    (void)blas;
    (void)ast;
    fputs("Function 'getBlasInAst' is not implemented yet", stderr);
    exit(1);
}

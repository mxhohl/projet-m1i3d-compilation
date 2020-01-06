/*!
 * \file blas.h
 * Contient toutes les fonctions et structures liés aux BasicLinear Algebra 
 * Subprograms (BLAS).
 */

#ifndef HEADER_BLAS
#define HEADER_BLAS

#include "ast.h"

typedef struct s_blas {
    char* name;
    ASTNode* root;
} BLAS;

BLAS* blasCreate(char* name, ASTNode* root);

void blasFree(BLAS* blas);

ASTNode** getBlasInAst(BLAS* blas, ASTNode* ast);

#endif /* HEADER_BLAS */

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

/*!
 * Charge les BLAS dans le mémoire. Doit être libérer avec freeAllBlas.
 * \param count Le nombre des BLASs chargés.
 * \return La liste des BLASs chargés.
 */
BLAS** loadBlas(size_t* count);

/*!
 * Libère la mémoire d'une liste de BLAS.
 * \param blas La liste des BLASs à libérer.
 * \param count Le nombre des BLASs à libérer.
 */
void freeAllBlas(BLAS** blas, size_t count);

/*!
 * Remplace les BLAS par des appels de fonctions dans un AST.
 * \param blas La liste de BLASs à remplacer.
 * \param count Le nombre de BLASs dans la liste.
 * \param ast Un pointeur vers l'AST à modifier (un pointeur pour pouvoir 
 * modifier le nœud racine).
 * \return Le nombre de blas trouvés et remplacés.
 */
size_t replaceBlasInAst(BLAS** blas, size_t count, ASTNode** ast);

#endif /* HEADER_BLAS */

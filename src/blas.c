#include "blas.h"

#include "logging.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**************************************************/
/**********       Fonctions Outils       **********/
/**************************************************/

static char* copyStr(char* str) {
    char* newStr = malloc(sizeof(char) * (strlen(str) + 1));
    if (!newStr) {
        logError(
            "Impossible d'allouer la mémoire pour dupliquer "
            "la chaine '%s' du BLAS.\n",
            str
        );
        return NULL;
    }
    strcpy(newStr, str);
    return newStr;
}

static BLAS* createBlas(char* name, ASTNode* root) {
    BLAS* blas = malloc(sizeof(struct s_blas));

    if (blas) {
        blas->name = copyStr(name);
        blas->root = root;
    }

    return blas;
}

static void freeBlas(BLAS* blas) {
    free(blas->name);
    astFree(blas->root);
    free(blas);
}

static ASTNode* createASTNode(astNodeType type) {
    ASTNode* newNode = malloc(sizeof(struct s_astNode));
    if (!newNode) {
        logError(
            "Impossible d'allouer la mémoire pour les paramètres "
            "d'appel du BLAS.\n"
        );
        return NULL;
    }
    newNode->type = type;
    return newNode;
}

static void replaceSubTree(ASTNode** subTreePtr, char* funcName, 
                           char** nameRefV, size_t nameRefCount) {
    ASTNode* callParameters = createASTNode(AST_INST_LIST);
    if (!callParameters) {
        return;
    }
    callParameters->instructionList.current = NULL;
    callParameters->instructionList.next = NULL;

    size_t i;
    ASTNode* currentList = callParameters;
    for (i = 0; i < nameRefCount; ++i) {
        ASTNode* ref = createASTNode(AST_VARIABLE_REF);
        if (!ref) {
            return;
        }
        ref->variableRef = copyStr(nameRefV[i]);

        currentList->instructionList.current = ref;
        
        ASTNode* iList = createASTNode(AST_INST_LIST);
        if (!iList) {
            return;
        }
        iList->instructionList.current = iList->instructionList.next = NULL;

        currentList->instructionList.next = iList;
        currentList = iList;
    }

    ASTNode* newNode = astCreateOperatorCall(
        astCreateVariableRef(funcName),
        callParameters
    );

    astFree(*subTreePtr);
    *subTreePtr = newNode;
}

static ASTNode** getSubTreeLocation(ASTNode* tree, ASTNode* subtree) {
    /* 
        TODO: tester les paramètres en plus des types et prendre en compte 
        les noms de variables
    */
    if (tree->type == subtree->type) {
        /* Switch tree->type */
            /* 
                Faire un && sur tout les retours de getSubTreeLocation sur 
                les enfants de tree et subtree.
                Exemple d'un cas:
                    if (getSubTreeLocation(tree->loop.condition, subtree->loop.condition) 
                     && getSubTreeLocation(tree->loop.body, subtree->loop.condition)) {
                         return &tree;
                    }
            */
    }
    
    ASTNode** first = NULL;
    ASTNode** second = NULL;

    switch (tree->type){
    case AST_INST_LIST:
        first = getSubTreeLocation(tree->instructionList.current, subtree);
        second = getSubTreeLocation(tree->instructionList.next, subtree);
        break;
    case AST_LOOP:
        first = getSubTreeLocation(tree->loop.body, subtree);
        break;
    case AST_BRANCH:
        if (tree->branch.ifBody) {
            first = getSubTreeLocation(tree->branch.ifBody, subtree);
        }
        if (tree->branch.elseBody) {
            second = getSubTreeLocation(tree->branch.elseBody, subtree);
        }
        break;
    default:
        break;
    }

    if (first) {
        return first;
    } else if (second) {
        return second;
    }
    return NULL;
}

static size_t replaceSingleBlasInAst(BLAS* blas, ASTNode** ast) {
    ASTNode** subtree;
    char* varNameRefI;
    char** varNameRefV;
    size_t varNameRefCount = 0;

    if ((subtree = getSubTreeLocation(*ast, blas->root))) {
        replaceSubTree(subtree, blas->name, varNameRefV, varNameRefCount);
        return 1;
    }
    return 0;
}


/**************************************************/
/**********        Implantations         **********/
/**************************************************/

BLAS** loadBlas(size_t* count) {
    *count = 1; /* On a uniquement le Level 0 */
    BLAS** blas = malloc(sizeof(struct s_blas*) * *count);
    if (!blas) {
        logError("Impossible d'allouer la mémoire pour la liste de BLAS.\n");
        *count = 0;
        return NULL;
    }

    /* Level 0
     * a = a + b * c;
     * mulacc(a, b, a);
     */
    blas[0] = createBlas(
        "mulacc", 
        astCreateVarAssignment(
            "a",
            astCreateOperatorAdd(
                astCreateVariableRef("a"),
                astCreateOperatorMultiply(
                    astCreateVariableRef("b"),
                    astCreateVariableRef("c")
                )
            )
        )
    );
    if (!blas[0]) {
        logError("Impossible d'allouer la mémoire pour le BLAS 'mulacc'.\n");
        *count = 0;
        return NULL;
    }

    return blas;
}

void freeAllBlas(BLAS** blas, size_t count) {
    size_t i;
    for (i = 0; i < count; ++i) {
        freeBlas(blas[i]);
    }
    free(blas);
}

size_t replaceBlasInAst(BLAS** blas, size_t count, ASTNode** ast) {
    
    size_t replaceCount = 0;
    size_t i;

    for(i = 0; i < count; ++i) {
        replaceCount += replaceSingleBlasInAst(blas[i], ast);
    }

    return replaceCount;
}

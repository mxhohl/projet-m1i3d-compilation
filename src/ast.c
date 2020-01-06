#include <stdlib.h>
#include <stdio.h>

#include "ast.h"


/**************************************************/
/**********       Fonctions Outils       **********/
/**************************************************/

static ASTNode* astCreateUnaryOperator(ASTNode* child, astNodeType type) {
    ASTNode* node;

    if ((node = malloc(sizeof(struct s_astNode)))) {
        node->type = type;
        node->opPlus = child;
    }

    return node;
}

static ASTNode* astCreateBinaryOperator(ASTNode* right, ASTNode* left, 
                                        astNodeType type) {
    ASTNode* node;

    if ((node = malloc(sizeof(struct s_astNode)))) {
        node->type = type;
        node->opAdd.right = right;
        node->opAdd.left = left;
    }

    return node;
}


/**************************************************/
/**********        Implantations         **********/
/**************************************************/

void astFree(ASTNode* ast) {
    if (!ast) {
        return;
    }

    switch (ast->type) {
    case AST_STATIC_DOUBLE:
    case AST_STATIC_INT:
        break;
    case AST_OP_PLUS:
    case AST_OP_MINUS:
    case AST_OP_INCREMENT:
    case AST_OP_DECREMENT:
        astFree(ast->opPlus);
        break;
    case AST_OP_ADD:
    case AST_OP_SUBSTRACT:
    case AST_OP_MULTIPLY:
    case AST_OP_DIVIDE:
    case AST_LOOP:
        astFree(ast->opAdd.right);
        astFree(ast->opAdd.left);
        break;
    case AST_BRANCH:
        astFree(ast->branch.condition);
        astFree(ast->branch.ifBody);
        astFree(ast->branch.elseBody);
        break;
    default:
        fprintf(stderr, "Unknown ASTNode type \"%d\".", ast->type);
        break;
    }

    free(ast);
}

ASTNode* astCreateStaticDouble(double value) {
    ASTNode* node;

    if ((node = malloc(sizeof(struct s_astNode)))) {
        node->type = AST_STATIC_DOUBLE;
        node->staticDouble = value;
    }

    return node;
}

ASTNode* astCreateStaticInt(int value) {
    ASTNode* node;

    if ((node = malloc(sizeof(struct s_astNode)))) {
        node->type = AST_STATIC_INT;
        node->staticInt = value;
    }

    return node;
}

ASTNode* astCreateVariableRef(char* varName) {
    ASTNode* node;

    if((node = malloc(sizeof(struct s_astNode)))) {
        node->type = AST_VARIABLE_REF;
        node->variableRef = varName;
    }

    return node;
}

ASTNode* astCreateOperatorPlus(ASTNode* right) {
    return astCreateUnaryOperator(right, AST_OP_PLUS);
}

ASTNode* astCreateOperatorMinus(ASTNode* right) {
    return astCreateUnaryOperator(right, AST_OP_MINUS);
}

ASTNode* astCreateOperatorAdd(ASTNode* right, ASTNode* left) {
    return astCreateBinaryOperator(right, left, AST_OP_ADD);
}

ASTNode* astCreateOperatorSubstract(ASTNode* right, ASTNode* left) {
    return astCreateBinaryOperator(right, left, AST_OP_SUBSTRACT);
}

ASTNode* astCreateOperatorMultiply(ASTNode* right, ASTNode* left) {
    return astCreateBinaryOperator(right, left, AST_OP_MULTIPLY);
}

ASTNode* astCreateOperatorDivide(ASTNode* right, ASTNode* left) {
    return astCreateBinaryOperator(right, left, AST_OP_DIVIDE);
}

ASTNode* astCreateOperatorIncrement(ASTNode* right) {
    return astCreateUnaryOperator(right, AST_OP_INCREMENT);
}

ASTNode* astCreateOperatorDecrement(ASTNode* right) {
    return astCreateUnaryOperator(right, AST_OP_DECREMENT);
}

ASTNode* astCreateOperatorEqual(ASTNode* right, ASTNode* left) {
    return astCreateBinaryOperator(right, left, AST_OP_EQ);
}

ASTNode* astCreateOperatorNotEqual(ASTNode* right, ASTNode* left) {
    return astCreateBinaryOperator(right, left, AST_OP_NEQ);
}

ASTNode* astCreateAssignment(char* varName, ASTNode* value) {
    ASTNode* node;

    if ((node = malloc(sizeof(struct s_astAssignment)))) {
        node->type = AST_ASSIGN;
        node->assignment.varName = varName;
        node->assignment.value = value;
    }

    return node;
}

ASTNode* astCreateBranch(ASTNode* condition, 
                         ASTNode* ifBody, 
                         ASTNode* elseBody) {
    ASTNode* node;

    if ((node = malloc(sizeof(struct s_astNode)))) {
        node->type = AST_BRANCH;
        node->branch.condition = condition;
        node->branch.ifBody = ifBody;
        node->branch.elseBody = elseBody;
    }

    return node;
}

ASTNode* astCreateLoop(ASTNode* condition, ASTNode* body) {
    return astCreateBinaryOperator(condition, body, AST_LOOP);
}

ASTNode* astCreateInstructionList(ASTNode* current, ASTNode* next) {
    return astCreateBinaryOperator(current, next, AST_INST_LIST);
}

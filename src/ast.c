#include <stdlib.h>

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

static ASTNode* astCreateBinaryOperator(ASTNode* first, ASTNode* second, 
                                        astNodeType type) {
    ASTNode* node;

    if ((node = malloc(sizeof(struct s_astNode)))) {
        node->type = type;
        node->opAdd.right = first;
        node->opAdd.left = second;
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
    case AST_VARIABLE_REF:
    case AST_VAR_DECLARATION:
    case AST_ARRAY_DECLARATION:
    case AST_PRINTF:
        break;

    case AST_OP_PLUS:
    case AST_OP_MINUS:
    case AST_OP_PREF_INCREMENT:
    case AST_OP_PREF_DECREMENT:
    case AST_OP_POST_INCREMENT:
    case AST_OP_POST_DECREMENT:
    case AST_OP_NOT:
        astFree(ast->opPlus);
        break;

    case AST_VAR_ASSIGN:
        astFree(ast->varAssignment.value);
        break;
    
    case AST_ARRAY_ASSIGN:
        astFree(ast->arrayAssignment.value);
        astFree(ast->arrayAssignment.pos);
        break;

    case AST_OP_ADD:
    case AST_OP_SUBSTRACT:
    case AST_OP_MULTIPLY:
    case AST_OP_DIVIDE:
    case AST_OP_LO:
    case AST_OP_LE:
    case AST_OP_GT:
    case AST_OP_GE:
    case AST_OP_EQ:
    case AST_OP_NEQ:
    case AST_OP_AND:
    case AST_OP_OR:
    case AST_LOOP:
    case AST_INST_LIST:
    case AST_OP_ARRAY_ACCESS:
    case AST_OP_CALL:
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

void astPrint(ASTNode* ast, FILE* out) {
    fprintf(out, "ICI, UN AST (si si, je vous jure)\n");
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

ASTNode* astCreateOperatorPlus(ASTNode* child) {
    return astCreateUnaryOperator(child, AST_OP_PLUS);
}

ASTNode* astCreateOperatorMinus(ASTNode* child) {
    return astCreateUnaryOperator(child, AST_OP_MINUS);
}

ASTNode* astCreateOperatorAdd(ASTNode* left, ASTNode* right) {
    return astCreateBinaryOperator(right, left, AST_OP_ADD);
}

ASTNode* astCreateOperatorSubstract(ASTNode* left, ASTNode* right) {
    return astCreateBinaryOperator(right, left, AST_OP_SUBSTRACT);
}

ASTNode* astCreateOperatorMultiply(ASTNode* left, ASTNode* right) {
    return astCreateBinaryOperator(right, left, AST_OP_MULTIPLY);
}

ASTNode* astCreateOperatorDivide(ASTNode* left, ASTNode* right) {
    return astCreateBinaryOperator(right, left, AST_OP_DIVIDE);
}

ASTNode* astCreateOperatorPrefIncrement(ASTNode* child) {
    return astCreateUnaryOperator(child, AST_OP_PREF_INCREMENT);
}

ASTNode* astCreateOperatorPrefDecrement(ASTNode* child) {
    return astCreateUnaryOperator(child, AST_OP_PREF_DECREMENT);
}

ASTNode* astCreateOperatorPostIncrement(ASTNode* child) {
    return astCreateUnaryOperator(child, AST_OP_POST_INCREMENT);
}

ASTNode* astCreateOperatorPostDecrement(ASTNode* child) {
    return astCreateUnaryOperator(child, AST_OP_POST_DECREMENT);
}

ASTNode* astCreateOperatorLower(ASTNode* left, ASTNode* right) {
    return astCreateBinaryOperator(right, left, AST_OP_LO);
}

ASTNode* astCreateOperatorLowerEqual(ASTNode* left, ASTNode* right) {
    return astCreateBinaryOperator(right, left, AST_OP_LE);
}

ASTNode* astCreateOperatorGreater(ASTNode* left, ASTNode* right) {
    return astCreateBinaryOperator(right, left, AST_OP_GT);
}

ASTNode* astCreateOperatorGreaterEqual(ASTNode* left, ASTNode* right) {
    return astCreateBinaryOperator(right, left, AST_OP_GE);
}

ASTNode* astCreateOperatorEqual(ASTNode* left, ASTNode* right) {
    return astCreateBinaryOperator(right, left, AST_OP_EQ);
}

ASTNode* astCreateOperatorNotEqual(ASTNode* left, ASTNode* right) {
    return astCreateBinaryOperator(right, left, AST_OP_NEQ);
}

ASTNode* astCreateOperatorNot(ASTNode* child) {
    return astCreateUnaryOperator(child, AST_OP_NOT);
}

ASTNode* astCreateOperatorAnd(ASTNode* left, ASTNode* right) {
    return astCreateBinaryOperator(right, left, AST_OP_AND);
}

ASTNode* astCreateOperatorOr(ASTNode* left, ASTNode* right) {
    return astCreateBinaryOperator(right, left, AST_OP_OR);
}

ASTNode* astCreateOperatorArrayAccess(ASTNode* array, ASTNode* index) {
    return astCreateBinaryOperator(array, index, AST_OP_ARRAY_ACCESS);
}

ASTNode* astCreateOperatorCall(ASTNode* function, ASTNode* parameters) {
    if (parameters && parameters->type != AST_INST_LIST) {
        fputs(
            "\033[1;33mLe paramètres 'parameters' d'un appel de "
            "fonction doit être du type 'AST_INST_LIST'\033[0m\n", 
            stderr
        );
        return NULL;
    }
    return astCreateBinaryOperator(function, parameters, AST_OP_CALL);
}

ASTNode* astCreateVarDeclaration(char* varName) {
    ASTNode* node;

    if((node = malloc(sizeof(struct s_astNode)))) {
        node->type = AST_VAR_DECLARATION;
        node->varDeclaration = varName;
    }

    return node;
}

ASTNode* astCreateArrayDeclaration(char* varName, size_t size) {
    ASTNode* node;

    if((node = malloc(sizeof(struct s_astNode)))) {
        node->type = AST_ARRAY_DECLARATION;
        node->arrayDeclaration.varName = varName;
        node->arrayDeclaration.size = size;
    }

    return node;
}

ASTNode* astCreateVarAssignment(char* varName, ASTNode* value) {
    ASTNode* node;

    if ((node = malloc(sizeof(struct s_astNode)))) {
        node->type = AST_VAR_ASSIGN;
        node->varAssignment.varName = varName;
        node->varAssignment.value = value;
    }

    return node;
}

ASTNode* astCreateArrayAssignment(char* varName, ASTNode* pos, ASTNode* value) {
    ASTNode* node;

    if ((node = malloc(sizeof(struct s_astNode)))) {
        node->type = AST_ARRAY_ASSIGN;
        node->arrayAssignment.varName = varName;
        node->arrayAssignment.pos = pos;
        node->arrayAssignment.value = value;
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

ASTNode* astCreateForLoop(ASTNode* init, 
                          ASTNode* condition,
                          ASTNode* update,
                          ASTNode* body) {
    return astCreateInstructionList(
        init,
        astCreateLoop(
            condition,
            astCreateInstructionList(
                body,
                update
            )
        )
    );
}

ASTNode* astCreateInstructionList(ASTNode* current, ASTNode* next) {
    return astCreateBinaryOperator(current, next, AST_INST_LIST);
}

ASTNode* astCreatePrintf(char* params) {
    ASTNode* node;

    if ((node = malloc(sizeof(struct s_astNode)))) {
        node->type = AST_PRINTF;
        node->printf = params;
    }

    return node;
}

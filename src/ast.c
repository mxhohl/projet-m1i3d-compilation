#include <stdlib.h>
#include <string.h>

#include "logging.h"
#include "ast.h"


/**************************************************/
/**********       Fonctions Outils       **********/
/**************************************************/

static ASTNode* createUnaryOperator(ASTNode* child, astNodeType type) {
    ASTNode* node;

    if ((node = malloc(sizeof(struct s_astNode)))) {
        node->type = type;
        node->opPlus = child;
    }

    return node;
}

static ASTNode* createBinaryOperator(ASTNode* first, ASTNode* second, 
                                     astNodeType type) {
    ASTNode* node;

    if ((node = malloc(sizeof(struct s_astNode)))) {
        node->type = type;
        node->opAdd.right = first;
        node->opAdd.left = second;
    }

    return node;
}

static char* copyStr(char* str) {
    char* newStr = malloc(sizeof(char) * (strlen(str) + 1));
    if (!newStr) {
        logError(
            "Impossible d'allouer la mémoire pour dupliquer "
            "la chaine '%s' de l'AST.\n",
            str
        );
        return NULL;
    }
    strcpy(newStr, str);
    return newStr;
}

static void printAst(ASTNode* root, FILE* out, size_t depth, size_t state) {
    size_t i;

    for (i = 0; i < depth; ++i) {
        if (depth > 0 && state & (1 << i)) {
            fprintf(out, "│  ");
        } else {
            fprintf(out, "   ");
        }
    }

    if (state & (1 << depth)) {
        fprintf(out, "├");
    } else {
        fprintf(out, "└");
    }

    if (!root) {
        fprintf(out, "○\n");
        return;
    }

    switch (root->type) {
    case AST_STATIC_DOUBLE:
        fprintf(out, "[Static Double: %f\n", root->staticDouble);
        break;
    case AST_STATIC_INT:
        fprintf(out, "[Static Int: %d\n", root->staticInt);
        break;
    case AST_VARIABLE_REF:
        fprintf(out, "[Variable Reference: %s\n", root->variableRef);
        break;
    case AST_INST_LIST:
        fprintf(out, "[Instruction List\n");
        printAst(
            root->instructionList.current, out, 
            depth +1, state | (1 << (depth +1))
        );
        printAst(
            root->instructionList.next, out, 
            depth +1, state
        );
        break;
    
    default:
        fprintf(out, "[NOT IMPLEMENTED NODE\n");
        break;
    }
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

    case AST_VARIABLE_REF:
    case AST_VAR_DECLARATION:
    case AST_PRINTF:
        free(ast->variableRef);
        break;

    case AST_ARRAY_DECLARATION:
        free(ast->arrayDeclaration.varName);
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
        free(ast->varAssignment.varName);
        astFree(ast->varAssignment.value);
        break;
    
    case AST_ARRAY_ASSIGN:
        free(ast->arrayAssignment.varName);
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
    printAst(ast, out, 0, 0);
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
        node->variableRef = copyStr(varName);
    }

    return node;
}

ASTNode* astCreateOperatorPlus(ASTNode* child) {
    return createUnaryOperator(child, AST_OP_PLUS);
}

ASTNode* astCreateOperatorMinus(ASTNode* child) {
    return createUnaryOperator(child, AST_OP_MINUS);
}

ASTNode* astCreateOperatorAdd(ASTNode* left, ASTNode* right) {
    return createBinaryOperator(right, left, AST_OP_ADD);
}

ASTNode* astCreateOperatorSubstract(ASTNode* left, ASTNode* right) {
    return createBinaryOperator(right, left, AST_OP_SUBSTRACT);
}

ASTNode* astCreateOperatorMultiply(ASTNode* left, ASTNode* right) {
    return createBinaryOperator(right, left, AST_OP_MULTIPLY);
}

ASTNode* astCreateOperatorDivide(ASTNode* left, ASTNode* right) {
    return createBinaryOperator(right, left, AST_OP_DIVIDE);
}

ASTNode* astCreateOperatorPrefIncrement(ASTNode* child) {
    return createUnaryOperator(child, AST_OP_PREF_INCREMENT);
}

ASTNode* astCreateOperatorPrefDecrement(ASTNode* child) {
    return createUnaryOperator(child, AST_OP_PREF_DECREMENT);
}

ASTNode* astCreateOperatorPostIncrement(ASTNode* child) {
    return createUnaryOperator(child, AST_OP_POST_INCREMENT);
}

ASTNode* astCreateOperatorPostDecrement(ASTNode* child) {
    return createUnaryOperator(child, AST_OP_POST_DECREMENT);
}

ASTNode* astCreateOperatorLower(ASTNode* left, ASTNode* right) {
    return createBinaryOperator(right, left, AST_OP_LO);
}

ASTNode* astCreateOperatorLowerEqual(ASTNode* left, ASTNode* right) {
    return createBinaryOperator(right, left, AST_OP_LE);
}

ASTNode* astCreateOperatorGreater(ASTNode* left, ASTNode* right) {
    return createBinaryOperator(right, left, AST_OP_GT);
}

ASTNode* astCreateOperatorGreaterEqual(ASTNode* left, ASTNode* right) {
    return createBinaryOperator(right, left, AST_OP_GE);
}

ASTNode* astCreateOperatorEqual(ASTNode* left, ASTNode* right) {
    return createBinaryOperator(right, left, AST_OP_EQ);
}

ASTNode* astCreateOperatorNotEqual(ASTNode* left, ASTNode* right) {
    return createBinaryOperator(right, left, AST_OP_NEQ);
}

ASTNode* astCreateOperatorNot(ASTNode* child) {
    return createUnaryOperator(child, AST_OP_NOT);
}

ASTNode* astCreateOperatorAnd(ASTNode* left, ASTNode* right) {
    return createBinaryOperator(right, left, AST_OP_AND);
}

ASTNode* astCreateOperatorOr(ASTNode* left, ASTNode* right) {
    return createBinaryOperator(right, left, AST_OP_OR);
}

ASTNode* astCreateOperatorArrayAccess(ASTNode* array, ASTNode* index) {
    return createBinaryOperator(array, index, AST_OP_ARRAY_ACCESS);
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
    return createBinaryOperator(function, parameters, AST_OP_CALL);
}

ASTNode* astCreateVarDeclaration(char* varName) {
    ASTNode* node;

    if((node = malloc(sizeof(struct s_astNode)))) {
        node->type = AST_VAR_DECLARATION;
        node->varDeclaration = copyStr(varName);
    }

    return node;
}

ASTNode* astCreateArrayDeclaration(char* varName, size_t size) {
    ASTNode* node;

    if((node = malloc(sizeof(struct s_astNode)))) {
        node->type = AST_ARRAY_DECLARATION;
        node->arrayDeclaration.varName = copyStr(varName);
        node->arrayDeclaration.size = size;
    }

    return node;
}

ASTNode* astCreateVarAssignment(char* varName, ASTNode* value) {
    ASTNode* node;

    if ((node = malloc(sizeof(struct s_astNode)))) {
        node->type = AST_VAR_ASSIGN;
        node->varAssignment.varName = copyStr(varName);
        node->varAssignment.value = value;
    }

    return node;
}

ASTNode* astCreateArrayAssignment(char* varName, ASTNode* pos, ASTNode* value) {
    ASTNode* node;

    if ((node = malloc(sizeof(struct s_astNode)))) {
        node->type = AST_ARRAY_ASSIGN;
        node->arrayAssignment.varName = copyStr(varName);
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
    return createBinaryOperator(condition, body, AST_LOOP);
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
    return createBinaryOperator(current, next, AST_INST_LIST);
}

ASTNode* astCreatePrintf(char* params) {
    ASTNode* node;

    if ((node = malloc(sizeof(struct s_astNode)))) {
        node->type = AST_PRINTF;
        node->printf = copyStr(params);
    }

    return node;
}

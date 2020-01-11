#include "c_generator.h"

static void printASTToFile(FILE* out, 
                           ASTNode* root, SymbolTable* st, 
                           size_t depth, int firstInLine);

static void printIndent(FILE* out, size_t depth, int onNewLine) {
    size_t i;
    if (onNewLine) {
        fprintf(out, "\n");
    }
    for (i = 0; i < depth; ++i) {
        fprintf(out, "    ");
    }
}

static int needSemicolon(astNodeType type) {
    return type != AST_INST_LIST 
        && type != AST_LOOP
        && type != AST_BRANCH;
}

static void printBlock(FILE* out, 
                       ASTNode* block, SymbolTable* st, 
                       size_t depth) {
    if (block) {
        fprintf(out, " {\n");
        printASTToFile(out, block, st, depth +1, 1);
        printIndent(out, depth, 1);
        fprintf(out, "}");
    } else {
        fprintf(out, ";");
    }
}

static void printASTToFile(FILE* out, 
                           ASTNode* root, SymbolTable* st, 
                           size_t depth, int firstInLine) {
    if (firstInLine && root->type != AST_INST_LIST) {
        printIndent(out, depth, 0);
    }

    switch (root->type) {
    case AST_STATIC_DOUBLE:
        fprintf(out, "%f", root->staticDouble);
        break;
    case AST_STATIC_INT:
        fprintf(out, "%d", root->staticInt);
        break;
    case AST_VARIABLE_REF:
        fprintf(out, "%s", root->variableRef);
        break;

    case AST_OP_PLUS:
        fprintf(out, "+");
        printASTToFile(out, root->opPlus, st, depth, 0);
        break;
    case AST_OP_MINUS:
        fprintf(out, "-");
        printASTToFile(out, root->opMinus, st, depth, 0);
        break;
    case AST_OP_ADD:
        printASTToFile(out, root->opAdd.left, st, depth, 0);
        fprintf(out, " + ");
        printASTToFile(out, root->opAdd.right, st, depth, 0);
        break;
    case AST_OP_SUBSTRACT:
        printASTToFile(out, root->opSubstract.left, st, depth, 0);
        fprintf(out, " - ");
        printASTToFile(out, root->opSubstract.right, st, depth, 0);
        break;
    case AST_OP_MULTIPLY:
        printASTToFile(out, root->opMultiply.left, st, depth, 0);
        fprintf(out, " * ");
        printASTToFile(out, root->opMultiply.right, st, depth, 0);
        break;
    case AST_OP_DIVIDE:
        printASTToFile(out, root->opDivide.left, st, depth, 0);
        fprintf(out, " / ");
        printASTToFile(out, root->opDivide.right, st, depth, 0);
        break;
    case AST_OP_PREF_INCREMENT:
        fprintf(out, "++");
        printASTToFile(out, root->opPrefIncrement, st, depth, 0);
        break;
    case AST_OP_PREF_DECREMENT:
        fprintf(out, "--");
        printASTToFile(out, root->opPrefDecrement, st, depth, 0);
        break;
    case AST_OP_POST_INCREMENT:
        printASTToFile(out, root->opPostIncrement, st, depth, 0);
        fprintf(out, "++");
        break;
    case AST_OP_POST_DECREMENT:
        printASTToFile(out, root->opPostDecrement, st, depth, 0);
        fprintf(out, "--");
        break;

    case AST_OP_LO:
        printASTToFile(out, root->opLower.left, st, depth, 0);
        fprintf(out, " < ");
        printASTToFile(out, root->opLower.right, st, depth, 0);
        break;
    case AST_OP_LE:
        printASTToFile(out, root->opLowerEq.left, st, depth, 0);
        fprintf(out, " <= ");
        printASTToFile(out, root->opLowerEq.right, st, depth, 0);
        break;
    case AST_OP_GT:
        printASTToFile(out, root->opGreater.left, st, depth, 0);
        fprintf(out, " > ");
        printASTToFile(out, root->opGreater.right, st, depth, 0);
        break;
    case AST_OP_GE:
        printASTToFile(out, root->opGreaterEq.left, st, depth, 0);
        fprintf(out, " >= ");
        printASTToFile(out, root->opGreaterEq.right, st, depth, 0);
        break;
    case AST_OP_EQ:
        printASTToFile(out, root->opEqual.left, st, depth, 0);
        fprintf(out, " == ");
        printASTToFile(out, root->opEqual.right, st, depth, 0);
        break;
    case AST_OP_NEQ:
        printASTToFile(out, root->opNotEqual.left, st, depth, 0);
        fprintf(out, " != ");
        printASTToFile(out, root->opNotEqual.right, st, depth, 0);
        break;
    case AST_OP_NOT:
        fprintf(out, "!");
        printASTToFile(out, root->opNot, st, depth, 0);
        break;
    case AST_OP_AND:
        printASTToFile(out, root->opAdd.left, st, depth, 0);
        fprintf(out, " && ");
        printASTToFile(out, root->opAdd.right, st, depth, 0);
        break;
    case AST_OP_OR:
        printASTToFile(out, root->opOr.left, st, depth, 0);
        fprintf(out, " || ");
        printASTToFile(out, root->opOr.right, st, depth, 0);
        break;

    case AST_OP_ARRAY_ACCESS:
        printASTToFile(out, root->opArrayAccess.array, st, depth, 0);
        fprintf(out, "[");
        printASTToFile(out, root->opArrayAccess.index, st, depth, 0);
        fprintf(out, "]");
        break;
    case AST_OP_CALL:
        printASTToFile(out, root->opCall.function, st, depth, 0);
        fprintf(out, "(");
        printASTToFile(out, root->opCall.parameters, st, depth, 0);
        fprintf(out, ")");
        break;

    case AST_VAR_DECLARATION:
        switch (stGetDataType(st, root->varDeclaration)) {
        case DT_INT:
            fprintf(out, "int ");
            break;
        case DT_DOUBLE:
            fprintf(out, "double ");
            break;
        default:
            break;
        }
        fprintf(out, "%s", root->varDeclaration);
        break;
    case AST_ARRAY_DECLARATION:
        switch (stGetDataType(st, root->arrayDeclaration.varName)) {
        case DT_INT:
            fprintf(out, "int ");
            break;
        case DT_DOUBLE:
            fprintf(out, "double ");
            break;
        default:
            break;
        }
        fprintf(
            out, 
            "%s[%lu]", 
            root->arrayDeclaration.varName, 
            root->arrayDeclaration.size
        );
        break;
    case AST_VAR_ASSIGN:
        fprintf(out, "%s = ", root->varAssignment.varName);
        printASTToFile(out, root->varAssignment.value, st, depth, 0);
        break;
    case AST_ARRAY_ASSIGN:
        fprintf(
            out, 
            "%s[",
            root->arrayAssignment.varName
        );
        printASTToFile(out, root->arrayAssignment.pos, st, depth, 0);
        fprintf(out, "] = ");
        printASTToFile(out, root->varAssignment.value, st, depth, 0);
        break;

    case AST_BRANCH:
        fprintf(out, "if (");
        printASTToFile(out, root->branch.condition, st, depth, 0);
        fprintf(out, ")");
        printBlock(out, root->branch.ifBody, st, depth);
        if (root->branch.elseBody) {
            fprintf(out, " else");
        }
        printBlock(out, root->branch.elseBody, st, depth);
        break;
    case AST_LOOP:
        fprintf(out, "while (");
        printASTToFile(out, root->loop.condition, st, depth, 0);
        fprintf(out, ")");
        printBlock(out, root->loop.body, st, depth);
        break;
    case AST_INST_LIST:
        if (root->instructionList.current) {
            printASTToFile(
                out, 
                root->instructionList.current, 
                st, 
                depth, 
                1
            );
            if (needSemicolon(root->instructionList.current->type)) {
                fprintf(out, ";");
            }
            fprintf(out, "\n");
        }
        if (root->instructionList.next) {
            printASTToFile(
                out, 
                root->instructionList.next, 
                st, 
                depth, 
                1
            );
            if (needSemicolon(root->instructionList.next->type)) {
                fprintf(out, ";");
            }
        }
        break;

    case AST_PRINTF:
        fprintf(out, "printf(%s)", root->printf);
        break;
    case AST_RETURN:
        fprintf(out, "return ");
        printASTToFile(out, root->instructionReturn, st, depth, 0);
        break;
    }
}

void astToC(FILE* out, ASTNode* root, SymbolTable* st) {
    fprintf(out, "int main() {\n");
    printASTToFile(out, root, st, 1, 0);
    fprintf(out, "}\n");
}

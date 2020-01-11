#ifndef HEADER_C_GENERATOR
#define HEADER_C_GENERATOR

#include "ast.h"
#include "symbol_table.h"
#include <stdio.h>

void astToC(FILE* out, ASTNode* root, SymbolTable* st);

#endif /* HEADER_C_GENERATOR */

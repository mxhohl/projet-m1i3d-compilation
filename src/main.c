#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

extern ASTNode* parse_file(FILE*);

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    const char* const filePath = "test.c";

    FILE* inFile = fopen(filePath, "r");
    if (!inFile) {
        fprintf(stderr, "Unable to open file %s\n", filePath);
        exit(1);
    }

    puts("Parsing...");

    ASTNode* ast = parse_file(inFile);

    if (!ast) {
        puts("Une erreur est survenue. Arret.");
        exit(10);
    }

    puts("Done");

    return 0;
}

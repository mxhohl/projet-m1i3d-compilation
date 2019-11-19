#ifndef HEADER_AST
#define HEADER_AST

typedef enum e_NodeType {
    CONST_FLOAT,
    CONST_INT
} NodeType;

typedef struct s_astNode {
    NodeType type;

    union {
        float floatValue;
        int intValue;
    };

} ASTNode;

#endif /* HEADER_AST */

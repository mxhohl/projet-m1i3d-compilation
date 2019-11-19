#ifndef HEADER_AST
#define HEADER_AST

typedef enum e_NodeType {
    STATIC_DOUBLE,
    STATIC_INT,
    PLUS,
    MINUS,
    ADD,
    SUBSTRACT,
    MULTIPLY,
    DIVIDE,
    INCREMENT,
    DECREMENT,
    BRANCH,
    LOOP
} NodeType;

struct s_astNode;

typedef struct s_astNode* astUnaryOperator;

typedef struct s_astBinaryOperator {
    struct s_astNode* right;
    struct s_astNode* left;
} astBinaryOperator;

typedef struct s_astBranch {
    struct s_astNode* condition;
    struct s_astNode* ifBody;
    struct s_astNode* elseBody;
} astBranch;

typedef struct s_astLoop {
    struct s_astNode* condition;
    struct s_astNode* body;
} astLoop;

typedef struct s_astNode {
    NodeType type;

    union {
        double staticDouble;
        int staticInt;
        astBinaryOperator opAdd;
        astBinaryOperator opSubstract;
        astBinaryOperator opMultiply;
        astBinaryOperator opDivide;
        astUnaryOperator opPlus;
        astUnaryOperator opMinus;
        astUnaryOperator opIncrement;
        astUnaryOperator opDecrement;
        astBranch branch;
        astLoop loop;
    };

} ASTNode;

#endif /* HEADER_AST */

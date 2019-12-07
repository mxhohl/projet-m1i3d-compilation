/*!
 * \file ast.h
 * Contient toutes les structures de donnés et les fonctions liés à aux AST.
 */

#ifndef HEADER_AST
#define HEADER_AST

/*!
 * \enum NodeType
 * Enum définissant les types de nœuds d'AST existants.
 */
typedef enum e_NodeType {
    AST_STATIC_DOUBLE,
    AST_STATIC_INT,
    AST_OP_PLUS,
    AST_OP_MINUS,
    AST_OP_ADD,
    AST_OP_SUBSTRACT,
    AST_OP_MULTIPLY,
    AST_OP_DIVIDE,
    AST_OP_INCREMENT,
    AST_OP_DECREMENT,
    AST_BRANCH,
    AST_LOOP
} NodeType;

struct s_astNode;

/*!
 * Type représentant un operateur unaire dans l'AST.
 */
typedef struct s_astNode* astUnaryOperator;

/*!
 * Type représentant un operateur binaire dans l'AST.
 */
typedef struct s_astBinaryOperator {
    struct s_astNode* right;    /*!< Le le membre de droite de l'operateur binaire */
    struct s_astNode* left;     /*!< Le le membre de gauche de l'operateur binaire */
} astBinaryOperator;

/*!
 * Type représentant un embranchement dans l'AST.
 */
typedef struct s_astBranch {
    struct s_astNode* condition;    /*!< La condition de l'embranchement */
    struct s_astNode* ifBody;       /*!< Le corps du bloque _if_ ou NULL*/
    struct s_astNode* elseBody;     /*!< Le corps du bloque _else_ ou NULL */
} astBranch;

/*!
 * Type représentant une boucle dans l'AST.
 */
typedef struct s_astLoop {
    struct s_astNode* condition;    /*!< La condition de la boucle */
    struct s_astNode* body;         /*!< Le corps de la boucle */
} astLoop;

/*!
 * Type représentant un nœud d'AST.
 */
typedef struct s_astNode {
    NodeType type;  /*!< Le type du nœud */

    union {
        /*! 
         * Champ définissant la valeur pour un nœud de type AST_STATIC_DOUBLE.
         */
        double staticDouble;
        /*! 
         * Champ définissant la valeur pour un nœud de type AST_STATIC_INT.
         */
        int staticInt;
        /*! 
         * Champ définissant la valeur pour un nœud de type AST_OP_ADD.
         */
        astBinaryOperator opAdd;
        /*! 
        * Champ définissant la valeur pour un nœud de type AST_OP_SUBSTRACT.
         */
        astBinaryOperator opSubstract;
        /*! 
         * Champ définissant la valeur pour un nœud de type AST_OP_MULTIPLY.
         */
        astBinaryOperator opMultiply;
        /*! 
         * Champ définissant la valeur pour un nœud de type AST_OP_DIVIDE.
         */
        astBinaryOperator opDivide;
        /*! 
         * Champ définissant la valeur pour un nœud de type AST_OP_PLUS.
         */
        astUnaryOperator opPlus;
        /*! 
         * Champ définissant la valeur pour un nœud de type AST_OP_MINUS.
         */
        astUnaryOperator opMinus;
        /*! 
         * Champ définissant la valeur pour un nœud de type AST_OP_INCREMENT.
         */
        astUnaryOperator opIncrement;
        /*! 
         * Champ définissant la valeur pour un nœud de type AST_OP_DECREMENT.
         */
        astUnaryOperator opDecrement;
        /*! 
         * Champ définissant la valeur pour un nœud de type AST_BRANCH.
         */
        astBranch branch;
        /*! 
         * Champ définissant la valeur pour un nœud de type AST_LOOP.
         */
        astLoop loop;
    };

} ASTNode;

/*!
 * Permet de libérer __toute__ la mémoire de l'AST.
 * \param ast L'AST à libérer.
 */
void astFree(ASTNode* ast);

/*!
 * Permet de créer une feuille de type Double statique.
 * \param value La valeur de la feuille.
 * \return Le nœud créé.
 */
ASTNode* astCreateStaticDouble(double value);

/*!
 * Permet de créer une feuille de type entier statique.
 * \param value La valeur de la feuille.
 * \return Le nœud créé.
 */
ASTNode* astCreateStaticInt(int value);

/*!
 * Permet de créer un nœud de type operateur plus unaire.
 * \param right Le nœud fils de l'operateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorPlus(ASTNode* right);

/*!
 * Permet de créer un nœud de type operateur moins unaire.
 * \param right Le nœud fils de l'operateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorMinus(ASTNode* right);

/*!
 * Permet de créer un nœud de type operateur d'addition.
 * \param right Le nœud fils à droite de l'operateur.
 * \param left Le nœud fils à gauche de l'operateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorAdd(ASTNode* right, ASTNode* left);

/*!
 * Permet de créer un nœud de type operateur de soustraction.
 * \param right Le nœud fils à droite de l'operateur.
 * \param left Le nœud fils à gauche de l'operateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorSubstract(ASTNode* right, ASTNode* left);

/*!
 * Permet de créer un nœud de type operateur de multiplication.
 * \param right Le nœud fils à droite de l'operateur.
 * \param left Le nœud fils à gauche de l'operateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorMultiply(ASTNode* right, ASTNode* left);

/*!
 * Permet de créer un nœud de type operateur de division.
 * \param right Le nœud fils à droite de l'operateur (diviseur).
 * \param left Le nœud fils à gauche de l'operateur (dividende).
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorDivide(ASTNode* right, ASTNode* left);

/*!
 * Permet de créer un nœud de type operateur d'incrément.
 * \param right Le nœud fils de l'operateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorIncrement(ASTNode* right);

/*!
 * Permet de créer un nœud de type operateur de décrément.
 * \param right Le nœud fils de l'operateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorDecrement(ASTNode* right);

/*!
 * Permet de créer un nœud de type branche (_if_, _if_/_else_).
 * \param condition La condition de l'embranchement
 * \param ifBranch Le nœud éxécuté si la condition est vraie (ou NULL si la 
 * branche _if_ est vide).
 * \param elseBranch Le nœud éxécuté si la condition est fausse (ou NULL si 
 * la branche _else_ est vide).
 * \return Le nœud créé.
 */
ASTNode* astCreateBranch(ASTNode* condition, 
                         ASTNode* ifBranch, 
                         ASTNode* elseBranch);

/*!
 * Permet de créer un nœud de type boucle (_while_, _for_).
 * \param condition La condition de l'embranchement
 * \param body Le corps de la boucle (ou NULL si le corps est vide).
 * \return Le nœud créé.
 */
ASTNode* astCreateLoop(ASTNode* condition, ASTNode* body);

#endif /* HEADER_AST */

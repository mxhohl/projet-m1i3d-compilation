/*!
 * \file ast.h
 * Contient toutes les structures de donnés et les fonctions liés à aux AST.
 */

#ifndef HEADER_AST
#define HEADER_AST

/*!
 * \enum astNodeType
 * Enum définissant les types de nœuds d'AST existants.
 */
typedef enum e_astNodeType {
    AST_STATIC_DOUBLE,
    AST_STATIC_INT,
    AST_VARIABLE_REF,

    AST_OP_PLUS,
    AST_OP_MINUS,
    AST_OP_ADD,
    AST_OP_SUBSTRACT,
    AST_OP_MULTIPLY,
    AST_OP_DIVIDE,
    AST_OP_INCREMENT,
    AST_OP_DECREMENT,
    AST_OP_EQ,
    AST_OP_NEQ,

    AST_ASSIGN,

    AST_BRANCH,
    AST_LOOP,
    AST_INST_LIST
} astNodeType;

struct s_astNode;

/*!
 * Type représentant un operateur unaire dans l'AST.
 */
typedef struct s_astNode* astUnaryOperator;

/*!
 * Type représentant un operateur binaire dans l'AST.
 */
typedef struct s_astBinaryOperator {
    struct s_astNode* right;    /*!< Le membre de droite de l'operateur binaire */
    struct s_astNode* left;     /*!< Le membre de gauche de l'operateur binaire */
} astBinaryOperator;

/*!
 * Type représentant un assignation.
 */
typedef struct s_astAssignment {
    char* varName;              /*!< Le nom de la variable qui prend la valeur */
    struct s_astNode* value;    /*!< Le nœud qui permet de déterminer la valeur de la variable */
} astAssignment;

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
 * Type représentant une suite d'instruction.
 */
typedef struct s_astInstructionList {
    struct s_astNode* current;  /*!< Le nœud actuel */
    struct s_astNode* next;     /*!< Le nœud suivant */
} astInstructionList;

/*!
 * Type représentant un nœud d'AST.
 */
typedef struct s_astNode {
    astNodeType type;  /*!< Le type du nœud */

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
         * Champ définissant le nom de la variable pour un nœud de type 
         * AST_VARIABLE_REF.
         */
        char* variableRef;
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
         * Champ définissant la valeur pour un noeud de type AST_OP_EQ.
         */
        astBinaryOperator opEqual;
        /*!
         * Champ définissant la valeur pour un noeud de type AST_OP_NEQ.
         */
        astBinaryOperator opNotEqual;
        /*!
         * Champ représentant la valeur d'une assignation de type AST_ASSIGN.
         */
        astAssignment assignment;
        /*! 
         * Champ définissant la valeur pour un nœud de type AST_BRANCH.
         */
        astBranch branch;
        /*! 
         * Champ définissant la valeur pour un nœud de type AST_LOOP.
         */
        astLoop loop;
        /*!
         * Champ définissant la valeur pour un nœud de type AST_INST_LIST.
         */
        astInstructionList instructionList;
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
 * Permet de créer une feuille de type reférence à une variable.
 * \param varName Le nom de la variable référencée.
 * \return Le nœud créé.
 */
ASTNode* astCreateVariableRef(char* varName);

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
 * Permet de créer un nœud de type operateur d'égalité.
 * \param left Le nœud fils de gauche de l'opérateur.
 * \param right Le nœud fils de droite de l'opérateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorEqual(ASTNode* right, ASTNode* left);

/*!
 * Permet de créer un nœud de type operateur d'inégalité.
 * \param left Le nœud fils de gauche de l'opérateur.
 * \param right Le nœud fils de droite de l'opérateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorNotEqual(ASTNode* right, ASTNode* left);

/*!
 * Permet de créer un nœud de type assignation.
 * \param varName Le nom de la variable qui doit prendre la valeur.
 * \param value Le nœud fils qui détermine la valeur de la variable;
 * \return Le nœud créé.
 */
ASTNode* astCreateAssignment(char* varName, ASTNode* value);

/*!
 * Permet de créer un nœud de type branche (_if_, _if_/_else_).
 * \param condition La condition de l'embranchement
 * \param ifBody Le nœud éxécuté si la condition est vraie (ou NULL si la 
 * branche _if_ est vide).
 * \param elseBody Le nœud éxécuté si la condition est fausse (ou NULL si 
 * la branche _else_ est vide).
 * \return Le nœud créé.
 */
ASTNode* astCreateBranch(ASTNode* condition, 
                         ASTNode* ifBody, 
                         ASTNode* elseBody);

/*!
 * Permet de créer un nœud de type boucle (_while_, _for_).
 * \param condition La condition de l'embranchement
 * \param body Le corps de la boucle (ou NULL si le corps est vide).
 * \return Le nœud créé.
 */
ASTNode* astCreateLoop(ASTNode* condition, ASTNode* body);

/*!
 * Permet de créer un nœud de type liste d'instruction.
 * Pour créer une véritable liste, il faut combiner plusieurs de ces nœud.
 * Par example :
 * ```
 * inst1;
 * inst2;
 * inst3;
 * ```
 * Devient :
 * ```
 *         astInstList
 *            +  +
 *   +--------+  +--------+
 *   +                    +
 * inst1              astInstList
 *                       + +
 *               +-------+ +--------+
 *               +                  +
 *             inst2            astInstList
 *                                 +  +
 *                          +------+  +-------+
 *                          +                 +
 *                        inst3             NULL
 * ```
 * \param current Le nœud actuel.
 * \param next Le nœud suivant.
 * \return Le nœud créé.
 */
ASTNode* astCreateInstructionList(ASTNode* current, ASTNode* next);

#endif /* HEADER_AST */

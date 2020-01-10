/*!
 * \file ast.h
 * Contient toutes les structures de donnés et les fonctions liés à aux AST.
 */

#ifndef HEADER_AST
#define HEADER_AST

#include <stddef.h>
#include <stdio.h>

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
    AST_OP_PREF_INCREMENT,
    AST_OP_PREF_DECREMENT,
    AST_OP_POST_INCREMENT,
    AST_OP_POST_DECREMENT,

    AST_OP_LO,
    AST_OP_LE,
    AST_OP_GT,
    AST_OP_GE,
    AST_OP_EQ,
    AST_OP_NEQ,
    AST_OP_NOT,
    AST_OP_AND,
    AST_OP_OR,

    AST_OP_ARRAY_ACCESS,
    AST_OP_CALL,

    AST_VAR_DECLARATION,
    AST_ARRAY_DECLARATION,
    AST_VAR_ASSIGN,
    AST_ARRAY_ASSIGN,

    AST_BRANCH,
    AST_LOOP,
    AST_INST_LIST,

    AST_PRINTF,
    AST_RETURN,
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
 * Type représentant un assignation de variable.
 */
typedef struct s_astVarAssignment {
    char* varName;              /*!< Le nom de la variable qui prend la valeur */
    struct s_astNode* value;    /*!< Le nœud qui permet de déterminer la valeur de la variable */
} astVarAssignment;

typedef struct s_astArrayAssignment {
    char* varName;              /*!< Le nom du tableau qui prend la valeur */
    struct s_astNode* pos;      /*!< La position dans la tableau */
    struct s_astNode* value;    /*!< Le nœud qui permet de déterminer la valeur de la variable */
} astArrayAssignment;

/*!
 * Type représentant une déclaration de tableau.
 */
typedef struct s_astArrayDeclaration {
    char* varName;  /*!< Le nom du tableau */
    size_t size;    /*!< La taille du tableau */
} astArrayDeclaration;

/*!
 * Type représentant l'accès à un tableau.
 */
typedef struct s_astOpArrayAccess {
    struct s_astNode* array;    /*!< Le tableau au quel on accède */
    struct s_astNode* index;    /*!< L'index de la cellule à accéder */
} astOpArrayAccess;

/*!
 * Type représentant un appel de fonction.
 */
typedef struct s_astOpCall {
    struct s_astNode* function;     /*!< La fonction à appeler */
    struct s_astNode* parameters;   /*!< Les paramètres de la fonction (doit être du type AST_INST_LIST) */
} astOpCall;

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
         * Champ définissant la valeur pour un nœud de type AST_OP_PREF_INCREMENT.
         */
        astUnaryOperator opPrefIncrement;
        /*! 
         * Champ définissant la valeur pour un nœud de type AST_OP_PREF_DECREMENT.
         */
        astUnaryOperator opPrefDecrement;
        /*! 
         * Champ définissant la valeur pour un nœud de type AST_OP_POST_INCREMENT.
         */
        astUnaryOperator opPostIncrement;
        /*! 
         * Champ définissant la valeur pour un nœud de type AST_OP_POST_DECREMENT.
         */
        astUnaryOperator opPostDecrement;
        /*! 
         * Champ définissant la valeur pour un nœud de type AST_OP_LO.
         */
        astBinaryOperator opLower;
        /*! 
         * Champ définissant la valeur pour un nœud de type AST_OP_LE.
         */
        astBinaryOperator opLowerEq;
        /*! 
         * Champ définissant la valeur pour un nœud de type .AST_OP_GT
         */
        astBinaryOperator opGreater;
        /*! 
         * Champ définissant la valeur pour un nœud de type AST_OP_GE.
         */
        astBinaryOperator opGreaterEq;
        /*!
         * Champ définissant la valeur pour un noeud de type AST_OP_EQ.
         */
        astBinaryOperator opEqual;
        /*!
         * Champ définissant la valeur pour un noeud de type AST_OP_NEQ.
         */
        astBinaryOperator opNotEqual;
        /*!
         * Champ définissant la valeur pour un noeud de type AST_OP_NOT.
         */
        astUnaryOperator opNot;
        /*!
         * Champ définissant la valeur pour un noeud de type AST_OP_AND.
         */
        astBinaryOperator opAnd;
        /*!
         * Champ définissant la valeur pour un noeud de type AST_OP_OR.
         */
        astBinaryOperator opOr;
        /*!
         * Champ définissant la valeur pour un noeud de type AST_OP_ARRAY_ACCESS.
         */
        astOpArrayAccess opArrayAccess;
        /*!
         * Champ définissant la valeur pour un noeud de type AST_OP_CALL.
         */
        astOpCall opCall;
        /*!
         * Champ représentant la valeur d'une assignation de type AST_VAR_DECLARATION.
         */
        char* varDeclaration;
        /*!
         * Champ représentant la valeur d'une assignation de type AST_ARRAY_DECLARATION.
         */
        astArrayDeclaration arrayDeclaration;
        /*!
         * Champ représentant la valeur d'une assignation de type AST_ASSIGN.
         */
        astVarAssignment varAssignment;
        /*!
         * Champ représentant la valeur d'une assignation de type AST_ASSIGN.
         */
        astArrayAssignment arrayAssignment;
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
        /*!
         * Champ définissant la valeur pour un nœud de type AST_PRINTF.
         */
        char* printf;
        /*!
         * Champ définissant la valeur pour un nœud de type AST_RETURN.
         */
        astUnaryOperator instructionReturn;
    };

} ASTNode;

/*!
 * Permet de libérer __toute__ la mémoire de l'AST.
 * \param ast L'AST à libérer.
 */
void astFree(ASTNode* ast);

/*!
 * Permet d'afficher un ast.
 * \param ast L'AST à afficher.
 * \param out Le fichier de sortie.
 */
void astPrint(ASTNode* ast, FILE* out);

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
 * \param child Le nœud fils de l'operateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorPlus(ASTNode* child);

/*!
 * Permet de créer un nœud de type operateur moins unaire.
 * \param child Le nœud fils de l'operateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorMinus(ASTNode* child);

/*!
 * Permet de créer un nœud de type operateur d'addition.
 * \param left Le nœud fils à gauche de l'operateur.
 * \param right Le nœud fils à droite de l'operateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorAdd(ASTNode* left, ASTNode* right);

/*!
 * Permet de créer un nœud de type operateur de soustraction.
 * \param left Le nœud fils à gauche de l'operateur.
 * \param right Le nœud fils à droite de l'operateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorSubstract(ASTNode* left, ASTNode* right);

/*!
 * Permet de créer un nœud de type operateur de multiplication.
 * \param left Le nœud fils à gauche de l'operateur.
 * \param right Le nœud fils à droite de l'operateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorMultiply(ASTNode* left, ASTNode* right);

/*!
 * Permet de créer un nœud de type operateur de division.
 * \param left Le nœud fils à gauche de l'operateur (diviseur).
 * \param right Le nœud fils à droite de l'operateur (dividende).
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorDivide(ASTNode* left, ASTNode* right);

/*!
 * Permet de créer un nœud de type operateur d'incrément.
 * \param child Le nœud fils de l'operateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorPrefIncrement(ASTNode* child);

/*!
 * Permet de créer un nœud de type operateur de décrément.
 * \param child Le nœud fils de l'operateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorPrefDecrement(ASTNode* child);

/*!
 * Permet de créer un nœud de type operateur d'incrément.
 * \param child Le nœud fils de l'operateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorPostIncrement(ASTNode* child);

/*!
 * Permet de créer un nœud de type operateur de décrément.
 * \param child Le nœud fils de l'operateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorPostDecrement(ASTNode* child);

/*!
 * Permet de créer un nœud de type operateur de comparaison inférieur à.
 * \param left Le nœud fils de gauche de l'opérateur.
 * \param right Le nœud fils de droite de l'opérateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorLower(ASTNode* left, ASTNode* right);

/*!
 * Permet de créer un nœud de type operateur de comparaison infèrieur ou égal à.
 * \param left Le nœud fils de gauche de l'opérateur.
 * \param right Le nœud fils de droite de l'opérateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorLowerEqual(ASTNode* left, ASTNode* right);

/*!
 * Permet de créer un nœud de type operateur de comparaison supérieur à.
 * \param left Le nœud fils de gauche de l'opérateur.
 * \param right Le nœud fils de droite de l'opérateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorGreater(ASTNode* left, ASTNode* right);

/*!
 * Permet de créer un nœud de type operateur de comparaison supérieur ou égal à.
 * \param left Le nœud fils de gauche de l'opérateur.
 * \param right Le nœud fils de droite de l'opérateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorGreaterEqual(ASTNode* left, ASTNode* right);

/*!
 * Permet de créer un nœud de type operateur d'égalité.
 * \param left Le nœud fils de gauche de l'opérateur.
 * \param right Le nœud fils de droite de l'opérateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorEqual(ASTNode* left, ASTNode* right);

/*!
 * Permet de créer un nœud de type operateur d'inégalité.
 * \param left Le nœud fils de gauche de l'opérateur.
 * \param right Le nœud fils de droite de l'opérateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorNotEqual(ASTNode* left, ASTNode* right);

/*!
 * Permet de créer un nœud de type operateur non.
 * \param child Le nœud fils de l'opérateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorNot(ASTNode* child);

/*!
 * Permet de créer un nœud de type operateur et.
 * \param left Le nœud fils de gauche de l'opérateur.
 * \param right Le nœud fils de droite de l'opérateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorAnd(ASTNode* left, ASTNode* right);

/*!
 * Permet de créer un nœud de type operateur ou.
 * \param left Le nœud fils de gauche de l'opérateur.
 * \param right Le nœud fils de droite de l'opérateur.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorOr(ASTNode* left, ASTNode* right);

/*!
 * Permet de créer un nœud de type operateur d'accès à un tableau.
 * \param array Le nœud du tableau.
 * \param index Le nœud de l'index.
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorArrayAccess(ASTNode* array, ASTNode* index);

/*!
 * Permet de créer un nœud de type operateur d'appel de fonction.
 * \param function Le nœud de la fonction.
 * \param parameters Le nœud des paramètres. Doit être du type AST_INST_LIST
 * \return Le nœud créé.
 */
ASTNode* astCreateOperatorCall(ASTNode* function, ASTNode* parameters);

/*!
 * Permet de créer un nœud de déclaration de variable.
 * \param varName Le nom de la variable déclarée.
 * \return Le nœud créé.
 */
ASTNode* astCreateVarDeclaration(char* varName);

/*!
 * Permet de créer un nœud de déclaration de tableau.
 * \param varName Le nom du tableau déclarée.
 * \param size La taille du tableau déclaré.
 * \return Le nœud créé.
 */
ASTNode* astCreateArrayDeclaration(char* varName, size_t size);

/*!
 * Permet de créer un nœud de type assignation de variable.
 * \param varName Le nom de la variable qui doit prendre la valeur.
 * \param value Le nœud fils qui détermine la valeur de la variable;
 * \return Le nœud créé.
 */
ASTNode* astCreateVarAssignment(char* varName, ASTNode* value);

/*!
 * Permet de créer un nœud de type assignation de tableau.
 * \param varName Le nom du tableau qui doit prendre la valeur.
 * \param pos La position dans le tableau.
 * \param value Le nœud fils qui détermine la valeur de la variable;
 * \return Le nœud créé.
 */
ASTNode* astCreateArrayAssignment(char* varName, ASTNode* pos, ASTNode* value);

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
 * Permet de créer les nœuds pour représenter une boucle for.
 * \param init Le nœud représentant l'initialisation de la boucle.
 * \param condition Le nœud de condition de la boucle.
 * \param update Le nœud de mise à jour à chaque itération.
 * \param body Le corps de la boucle.
 * \return Les nœuds créés.
 */
ASTNode* astCreateForLoop(ASTNode* init, 
                          ASTNode* condition,
                          ASTNode* update,
                          ASTNode* body);

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

/*!
 * Permet de créer un nœud de type printf. Il permet de réserver à printf un
 * traitement particulier.
 * \param params Les paramètres de printf.
 * \return Le nœud créé.
 */
ASTNode* astCreatePrintf(char* params);

/*!
 * Permet de créer un nœud de type return. Il permet de réserver à return un
 * traitement particulier.
 * \param expr L'expression que retourne le return.
 * \return Le nœud créé.
 */
ASTNode* astCreateReturn(ASTNode* expr);

#endif /* HEADER_AST */

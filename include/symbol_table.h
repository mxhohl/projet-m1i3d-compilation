/*!
 * \file symbol_table.h
 * Contient la structure de donnée Table de Symboles.
 * TODO:
 *   - L'implantation devrait être une hash table pas une linked list pour les
 *     performances.
 */

#ifndef HEADER_SYMBOL_TABLE
#define HEADER_SYMBOL_TABLE

#include <stdio.h>

typedef struct s_symbolTable SymbolTable;

typedef enum e_varType {
    VT_VARIABLE,
    VT_ARRAY,
    VT_UNKNOWN
} VarType;

typedef enum e_dataType {
    DT_INT,
    DT_DOUBLE,
    DT_UNKNOWN
} DataType;

/*!
 * Permet de créer une table des symboles. Celle-ci doit être libérée avec
 * `stFree`.
 * \return La table des symboles créé.
 */
SymbolTable* stCreate();

/*!
 * Permet de libérer la table des symboles.
 * \param st La table des symboles à libérer.
 */
void stFree(SymbolTable* st);

/*!
 * Permet de récuperer le nombre d'entrés dans la table.
 * \param st La table dont on veut la taille.
 * \return La taille de la table.
 */
size_t stLen(SymbolTable* st);

/*!
 * Permet d'afficher la table des symboles dans un fichier.
 * \param st La table des symboles à afficher.
 * \param out Le fichier où écrire la table des symboles.
 */
void stPrint(SymbolTable* st, FILE* out);

/*!
 * Permet d'ajouter un symbole de type variable à la table.
 * \param st La table où ajouter le symbole.
 * \param name Le nom du symbol à ajouter.
 * \param data_type Le type du symbol à ajouter.
 * \return 0 si le symbol à était ajouté, 1 si le symbole existe déjà et 
 * 100 si une erreur est survenue.
 */
int stAddVariableSymbol(SymbolTable* st, const char* name, DataType dataType);

/*!
 * Permet d'ajouter un symbole de type tableau à la table.
 * \param st La table où ajouter le symbole.
 * \param name Le nom du symbol à ajouter.
 * \param data_type Le type du symbol à ajouter.
 * \param size La taille du tableau.
 * \return 0 si le symbol à était ajouté, 1 si le symbole existe déjà et 
 * 100 si une erreur est survenue.
 */
int stAddArraySymbol(SymbolTable* st, 
                     const char* name, 
                     DataType dataType, 
                     size_t size);

/*!
 * Permet d'ajouter un valeur statiquede type int à la table des symboles.
 * \param st La table des symboles où ajouter le symbole.
 * \param value La valeur statique à ajouter.
 * \return Le nom donné à la valeur statique ou NULL si une erreur est survenue.
 */
const char* stAddStaticInt(SymbolTable* st, const int value);

/*!
 * Permet d'ajouter un valeur statiquede type souble à la table des symboles.
 * \param st La table des symboles où ajouter le symbole.
 * \param value La valeur statique à ajouter.
 * \return Le nom donné à la valeur statique ou NULL si une erreur est survenue.
 */
const char* stAddStaticDouble(SymbolTable* st, const double value);

/*!
 * Permet de verifier si un symbole est déjà dans la table.
 * \param st La table où regarder.
 * \param name Le nom du symbole à chercher.
 * \return Vrai si le symbole est présent, non sinon.
 */
int stSymbolExist(SymbolTable* st, const char* name);

/*!
 * Permet de récupérer le type de donné d'une variable par son nom.
 * \param st La table où chercher le symbole.
 * \param name Le nom du symbole recherché.
 * \return Le type du symbole recherché ou DT_UNKNOWN si le symbole 
 * n'existe pas.
 */
DataType stGetDataType(SymbolTable* st, const char* name);

/*!
 * Permet de récupérer le type de variable d'une variable par son nom.
 * \param st La table où chercher le symbole.
 * \param name Le nom du symbole recherché.
 * \return Le type du symbole recherché ou VT_UNKNOWN si le symbole 
 * n'existe pas.
 */
VarType stGetVarType(SymbolTable* st, const char* name);

/*!
 * Permet de définir le type des symbols ayant comme type de donné DT_UNKNOWN.
 * \param st La table où chercher les symboles.
 * \param dtype Le nouveau type des symboles.
 */
void stSetUnknownDataTypes(SymbolTable* st, DataType dtype);

/*!
 * Permet de savoir si un symbole est statique.
 * \param st La table où chercher.
 * \param name Le nom du symbole.
 * \return vrai si le symbole existe et est statique, faux sinon.
 */
int stIsStatic(SymbolTable* st, const char* name);

/*!
 * Permet de récupérer la valeur d'un symbole statique de type int.
 * \param st La table où chercher le symbole.
 * \param name Le nom du symbole recherché.
 * \return La valeur du symbole ou 0 si le symbole n'est pas statique ou 
 * n'existe pas.
 */
int stGetStaticIntValue(SymbolTable* st, const char* name);

/*!
 * Permet de récupérer la valeur d'un symbole statique de type double.
 * \param st La table où chercher le symbole.
 * \param name Le nom du symbole recherché.
 * \return La valeur du symbole ou 0 si le symbole n'est pas statique ou 
 * n'existe pas.
 */
double setGetStaticDoubleValue(SymbolTable* st, const char* name);

#endif /* HEADER_SYMBOL_TABLE */

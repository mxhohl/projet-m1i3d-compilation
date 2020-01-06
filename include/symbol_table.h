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
 * Permet d'ajouter un symbole à la table.
 * \param st La touble où ajouter le symbol.
 * \param bame Le nom du symbol à ajouter.
 * \param type Le type du symbol à ajouter.
 * \return 0 si le symbol à était ajouté, 1 si le symbole existe déjà et 
 * 100 si une erreur est survenue.
 */
int stAddSymbol(SymbolTable* st, char* name, DataType type);

/*!
 * Permet d'ajouter un valeur statiquede type int à la table des symboles.
 * \param st La table des symboles où ajouter le symbole.
 * \param value La valeur statique à ajouter.
 * \return Le nom donné à la valeur statique ou NULL si une erreur est survenue.
 */
const char* stAddStaticInt(SymbolTable* st, int value);

/*!
 * Permet d'ajouter un valeur statiquede type souble à la table des symboles.
 * \param st La table des symboles où ajouter le symbole.
 * \param value La valeur statique à ajouter.
 * \return Le nom donné à la valeur statique ou NULL si une erreur est survenue.
 */
const char* stAddStaticDouble(SymbolTable* st, double value);

/*!
 * Permet de verifier si un symbole est déjà dans la table.
 * \param st La table où regarder.
 * \param name Le nom du symbole à chercher.
 * \return Vrai si le symbole est présent, non sinon.
 */
int stSymbolExist(SymbolTable* st, char* name);

/*!
 * Permet de récupérer le type d'une variable par son nom.
 * \param st La table où chercher le symbole.
 * \param name Le nom du symbole recherché.
 * \return Le type du symbole recherché ou DT_UNKNOWN si le symbole 
 * n'existe pas.
 */
DataType stGetType(SymbolTable* st, char* name);

/*!
 * Permet de savoir si un symbole est statique.
 * \param st La table où chercher.
 * \param name Le nom du symbole.
 * \return vrai si le symbole existe et est statique, faux sinon.
 */
int stIsStatic(SymbolTable* st, char* name);

/*!
 * Permet de récupérer la valeur d'un symbole statique de type int.
 * \param st La table où chercher le symbole.
 * \param name Le nom du symbole recherché.
 * \return La valeur du symbole ou 0 si le symbole n'est pas statique ou 
 * n'existe pas.
 */
int stGetStaticIntValuePtr(SymbolTable* st, char* name);

/*!
 * Permet de récupérer la valeur d'un symbole statique de type double.
 * \param st La table où chercher le symbole.
 * \param name Le nom du symbole recherché.
 * \return La valeur du symbole ou 0 si le symbole n'est pas statique ou 
 * n'existe pas.
 */
double setGetStaticDoubleValuePtr(SymbolTable* st, char* name);

#endif /* HEADER_SYMBOL_TABLE */

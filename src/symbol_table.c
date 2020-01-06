#include "symbol_table.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>


/**************************************************/
/*                     TYPES                      */
/**************************************************/

typedef struct s_symbol {
    struct s_symbol* next;
    struct s_symbol* prev;

    char* name;
    DataType type;
    union u_staticValue {
        int i;
        double d;
    }* static_value;
} Symbol;

struct s_symbolTable {
    Symbol* first;
    Symbol* last;

    size_t count;
    size_t count_static;
};


/**************************************************/
/*               FONCTIONS OUTILS                 */
/**************************************************/

static void getTypeName(DataType type, char* name) {
    switch (type) {
    case DT_INT:
        strcpy(name, "int");
        break;
    case DT_DOUBLE:
        strcpy(name, "double");
        break;
    default:
        strcpy(name, "unknown");
        break;
    }
}

static Symbol* getSymbol(SymbolTable* st, char* name) {
    Symbol* current;
    for (current = st->first; current; current = current->next) {
        if (strcmp(name, current->name) == 0) {
            return current;
        }
    }
    return NULL;
}

static Symbol* addNewSymbol(SymbolTable* st, char* name, DataType type) {
    Symbol* newSymbol;
    if (!(newSymbol = malloc(sizeof(struct s_symbol)))) {
        return NULL;
    }

    newSymbol->name = name;
    newSymbol->type = type;
    newSymbol->static_value = NULL;

    newSymbol->next = NULL;
    newSymbol->prev = st->last;

    if (st->last) {
        st->last->next = newSymbol;
    }
    st->last = newSymbol;

    if (!st->first) {
        st->first = newSymbol;
    }

    ++st->count;

    return newSymbol;
}

/* Can be optimized for large numbers. 
 * See : https://stackoverflow.com/a/3069580 
 */
static size_t getNbLength(size_t nb) {
    if (nb == 0) {
        return 1;
    }

    return floor(log10(nb)) +1;
}

static Symbol* addStaticSymbol(SymbolTable* st, DataType type, char* name) {
    size_t nbDigit = getNbLength(st->count_static);

    if (!(name = malloc(sizeof(char) * (8 + nbDigit)))) {
        fputs(
            "Impossible d'allouer la mémoire pour le nom de symbole(static).",
            stderr
        );
        return NULL;
    }
    sprintf(name, "static_%lu", st->count_static);

    Symbol* newSymbol;
    if (!(newSymbol = addNewSymbol(st, name, type))) {
        return NULL;
    }

    newSymbol->static_value = malloc(sizeof(union u_staticValue));

    ++st->count_static;

    return newSymbol;
}

static void getValueStr(Symbol* s, char* strValue) {
    if (!s->static_value) {
        strcpy(strValue, "N/A");
        return;
    }

    switch (s->type) {
    case DT_INT:
        sprintf(strValue, "%d", s->static_value->i);
        break;
    case DT_DOUBLE:
        sprintf(strValue, "%f", s->static_value->d);
        break;
    default:
        strcpy(strValue, "unknown");
        break;
    }
}


/**************************************************/
/*                  DEFINITIONS                   */
/**************************************************/

SymbolTable* stCreate() {
    SymbolTable* st;

    if ((st = malloc(sizeof(struct s_symbolTable)))) {
        st->count = 0;
        st->count_static = 0;
        st->first = st->last = NULL;
    }

    return st;
}

void stFree(SymbolTable* st) {
    Symbol* current = st->first;
    Symbol* prev;
    while (current) {
        free(current->name);
        if (current->static_value) {
            free(current->static_value);
        }

        prev = current;
        current = current->next;
        free(prev);
    }
    free(st);
}

size_t stLen(SymbolTable* st) {
    return st->count;
}

void stPrint(SymbolTable* st, FILE* out) {
    char typeNameBuffer[8];
    char valueBuffer[64];
    Symbol* current;

    fprintf(out, "La table contient %lu entrés:\n", st->count);
    fprintf(out, "%-15s  %-7s  %-6s  %-10s\n", 
            "NAME", "TYPE", "STATIC", "VALUE"
    );
    for (current = st->first; current; current = current->next) {
        getTypeName(current->type, typeNameBuffer);
        getValueStr(current, valueBuffer);

        fprintf(out, "%-15.15s  %-7s  %-6s  %-10s\n", 
            current->name,
            typeNameBuffer,
            current->static_value ? "OUI" : "NON",
            valueBuffer
        );
    }
}

int stAddSymbol(SymbolTable* st, char* name, DataType type) {
    if (getSymbol(st, name)) {
        return 1;
    }

    char* nameBuff = malloc(sizeof(char) * (strlen(name) +1));
    strcpy(nameBuff, name);

    if (!addNewSymbol(st, nameBuff, type)) {
        return 100;
    }

    return 0;
}

const char* stAddStaticInt(SymbolTable* st, int value) {
    char* nameBuff = NULL;

    Symbol* newSymbol;
    if (!(newSymbol = addStaticSymbol(st, DT_INT, nameBuff))) {
        return NULL;
    }

    newSymbol->static_value->i = value;

    return nameBuff;
}

const char* stAddStaticDouble(SymbolTable* st, double value) {
    char* nameBuff = NULL;

    Symbol* newSymbol;
    if (!(newSymbol = addStaticSymbol(st, DT_DOUBLE, nameBuff))) {
        return NULL;
    }

    newSymbol->static_value->d = value;

    return nameBuff;
}

int stSymbolExist(SymbolTable* st, char* name) {
    return getSymbol(st, name) != NULL;
}

DataType stGetType(SymbolTable* st, char* name) {
    Symbol* symbol;
    if ((symbol = getSymbol(st, name))) {
        return symbol->type;
    }
    
    return DT_UNKNOWN;
}

int stIsStatic(SymbolTable* st, char* name) {
    Symbol* symbol = getSymbol(st, name);
    return symbol && symbol->static_value;
}

int stGetStaticIntValuePtr(SymbolTable* st, char* name) {
    Symbol* symbol = getSymbol(st, name);
    if (!symbol || !symbol->static_value) {
        return 0;
    }
    return symbol->static_value->i;
}

double setGetStaticDoubleValuePtr(SymbolTable* st, char* name) {
    Symbol* symbol = getSymbol(st, name);
    if (!symbol || !symbol->static_value) {
        return 0.;
    }
    return symbol->static_value->d;
}

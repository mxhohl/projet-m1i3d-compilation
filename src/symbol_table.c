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
    DataType data_type;
    VarType var_type;

    size_t array_size;

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

static void getDataTypeName(DataType type, char* name) {
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

static void getVarTypeName(VarType type, char* name) {
    switch (type) {
    case VT_VARIABLE:
        strcpy(name, "variable");
        break;
    case VT_ARRAY:
        strcpy(name, "tableau");
        break;
    case VT_CONSTANT:
        strcpy(name, "constant");
        break;
    default:
        strcpy(name, "unknown");
        break;
    }
}

static Symbol* getSymbol(SymbolTable* st, const char* name) {
    Symbol* current;
    for (current = st->first; current; current = current->next) {
        if (strcmp(name, current->name) == 0) {
            return current;
        }
    }
    return NULL;
}

static Symbol* addNewSymbol(SymbolTable* st, char* name, DataType dataType, VarType varType) {
    Symbol* newSymbol;
    if (!(newSymbol = malloc(sizeof(struct s_symbol)))) {
        return NULL;
    }

    newSymbol->name = name;
    newSymbol->data_type = dataType;
    newSymbol->var_type = varType;
    newSymbol->array_size = 0;
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

static Symbol* addStaticSymbol(SymbolTable* st, 
                               DataType dataType, 
                               char* name) {
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
    if (!(newSymbol = addNewSymbol(st, name, dataType, VT_VARIABLE))) {
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

    switch (s->data_type) {
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

static void getSizeStr(Symbol* s, char* strValue) {
    if (s->var_type != VT_ARRAY) {
        strcpy(strValue, "N/A");
        return;
    }
    sprintf(strValue, "%lu", s->array_size);
}


/**************************************************/
/*                  DEFINITIONS                   */
/**************************************************/

SymbolTable* stCreate() {
    SymbolTable* st;

    if ((st = malloc(sizeof(struct s_symbolTable)))) {
        st->count = 0;
        st->count_static = 0;
        st->first = NULL;
        st->last = NULL;
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
    char dataTypeNameBuffer[8];
    char varTypeNameBuffer[16];
    char valueBuffer[64];
    char sizeBuffer[32];
    Symbol* current;

    fprintf(out, "La table des symboles contient %lu entrés:\n", st->count);
    fprintf(out, "%-15s  %-7s  %-8s  %-6s  %-6s  %-10s\n", 
            "NAME", "DTYPE", "VTYPE", "TAILLE", "STATIC", "VALUE"
    );
    for (current = st->first; current; current = current->next) {
        getDataTypeName(current->data_type, dataTypeNameBuffer);
        getVarTypeName(current->var_type, varTypeNameBuffer);
        getValueStr(current, valueBuffer);
        getSizeStr(current, sizeBuffer);

        fprintf(out, "%-15.15s  %-7s  %-8s  %-6s  %-6s  %-10s\n", 
            current->name,
            dataTypeNameBuffer,
            varTypeNameBuffer,
            sizeBuffer,
            current->static_value ? "OUI" : "NON",
            valueBuffer
        );
    }
}

int stAddConstantSymbol(SymbolTable* st,char* name, DataType dataType, int value) {
    if (getSymbol(st, name)) {
        return 1;
    }

    char* nameBuff = malloc(sizeof(char) * (strlen(name) +1));
    Symbol* newSymbol;
    if (!(newSymbol = malloc(sizeof(struct s_symbol)))) {
        return 1;
    }
    strcpy(nameBuff, name);

    newSymbol->name = nameBuff;
    newSymbol->data_type = dataType;
    newSymbol->var_type = VT_CONSTANT;
    newSymbol->array_size = 0;
    newSymbol->static_value = malloc(sizeof(union u_staticValue));
    newSymbol->static_value->i = value;

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

    return 0;
}

int stAddVariableSymbol(SymbolTable* st, const char* name, DataType dataType) {
    if (getSymbol(st, name)) {
        return 1;
    }

    char* nameBuff = malloc(sizeof(char) * (strlen(name) +1));
    strcpy(nameBuff, name);

    if (!addNewSymbol(st, nameBuff, dataType, VT_VARIABLE)) {
        return 100;
    }

    return 0;
}

int stAddArraySymbol(SymbolTable* st, 
                     const char* name, 
                     DataType dataType, 
                     size_t size) {
    if (getSymbol(st, name)) {
        return 1;
    }

    char* nameBuff = malloc(sizeof(char) * (strlen(name) +1));
    strcpy(nameBuff, name);

    Symbol* newSymbol;
    if (!(newSymbol = addNewSymbol(st, nameBuff, dataType, VT_ARRAY))) {
        return 100;
    }

    newSymbol->array_size = size;

    return 0;
}

const char* stAddStaticInt(SymbolTable* st, const int value) {
    char* nameBuff = NULL;

    Symbol* newSymbol;
    if (!(newSymbol = addStaticSymbol(st, DT_INT, nameBuff))) {
        return NULL;
    }

    newSymbol->static_value->i = value;

    return nameBuff;
}

const char* stAddStaticDouble(SymbolTable* st, const double value) {
    char* nameBuff = NULL;

    Symbol* newSymbol;
    if (!(newSymbol = addStaticSymbol(st, DT_DOUBLE, nameBuff))) {
        return NULL;
    }

    newSymbol->static_value->d = value;

    return nameBuff;
}

int stSymbolExist(SymbolTable* st, const char* name) {
    return getSymbol(st, name) != NULL;
}

DataType stGetDataType(SymbolTable* st, const char* name) {
    Symbol* symbol;
    if ((symbol = getSymbol(st, name))) {
        return symbol->data_type;
    }
    
    return DT_UNKNOWN;
}

VarType stGetVarType(SymbolTable* st, const char* name) {
    Symbol* symbol;
    if ((symbol = getSymbol(st, name))) {
        return symbol->var_type;
    }
    
    return VT_UNKNOWN;
}

void stSetUnknownDataTypes(SymbolTable* st, DataType dtype) {
    Symbol* current;
    for (current = st->first; current; current = current->next) {
        if (current->data_type == DT_UNKNOWN) {
            current->data_type = dtype;
        }
    }
}

int stIsStatic(SymbolTable* st, const char* name) {
    Symbol* symbol = getSymbol(st, name);
    return symbol && symbol->static_value;
}

int stGetStaticIntValue(SymbolTable* st, const char* name) {
    Symbol* symbol = getSymbol(st, name);
    if (!symbol || !symbol->static_value) {
        return 0;
    }
    return symbol->static_value->i;
}

double setGetStaticDoubleValue(SymbolTable* st, const char* name) {
    Symbol* symbol = getSymbol(st, name);
    if (!symbol || !symbol->static_value) {
        return 0.;
    }
    return symbol->static_value->d;
}

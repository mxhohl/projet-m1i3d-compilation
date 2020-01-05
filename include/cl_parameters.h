/*!
 * \file cl_parameters.h
 * Contient les fonctions utiles pour gérere les paramètres de la ligne de 
 * commande.
 */

#ifndef HEADER_CL_PARAMETER
#define HEADER_CL_PARAMETER

typedef struct s_clParameters {
    int printAst;
    int printTos;
    char* outFile;
    char* inFile;
} clParameters;

clParameters* clGetParameters(int argc, char** argv);

void clFree(clParameters* cl);

void clPrintUsage();

void clPrintVersion();

#endif /* HEADER_CL_PARAMETER */

#include "cl_parameters.h"

#include "logging.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

clParameters* clGetParameters(int argc, char** argv) {
    int i;
    int waitingOutFile = 0;

    int printHelp = 0;
    int printVersion = 0;

    clParameters* parameters;
    if (!(parameters = calloc(1, sizeof(struct s_clParameters)))) {
        logError("Impossible d'allouter la mémoire pour les paramètres.");
        exit(1);
    }

    for (i = 1; i < argc; ++i) {
        if (waitingOutFile) {
            parameters->outFile = malloc(sizeof(char) * (strlen(argv[i]) +1));
            strcpy(parameters->outFile, argv[i]);
            waitingOutFile = 0;
        } else {
            if (strcmp(argv[i], "-version") == 0) {
                printVersion = 1;
            } else if (strcmp(argv[i], "-tos") == 0) {
                parameters->printTos = 1;
            } else if (strcmp(argv[i], "-ast") == 0) {
                parameters->printAst = 1;
            } else if (strcmp(argv[i], "-o") == 0) {
                waitingOutFile = 1;
            } else if (strcmp(argv[i], "-h") == 0) {
                printHelp = 1;
            } else if (argv[i][0] != '-') {
                parameters->inFile = malloc(sizeof(char) * (strlen(argv[i])+1));
                strcpy(parameters->inFile, argv[i]);
                ++i;
                break;
            } else {
                logError("Option '%s' inconnue.\n", argv[i]);
                clPrintUsage();
                exit(20);
            }
        }
    }

    int printTryHelp = i < argc;
    for (; i < argc; ++i) {
        logWarning(
            "Le fichier d'entré est déjà spécifié. "
            "Paramètre '%s' ignoré.\n", 
            argv[i]
        );
    }
    if (printTryHelp) {
        logMessage("Essayez 'ib3m -h' pour plus d'informations.\n");
    }

    if (printVersion) {
        clPrintVersion();
        if (!parameters->inFile) {
            exit(0);
        }
    } else if (printHelp && argc == 2) {
        clPrintUsage();
        clFree(parameters);
        exit(0);
    }

    if (!parameters->inFile) {
        logError("Le fichier d'entré n'a pas été spécifié.\n");
        clPrintUsage();
        clFree(parameters);
        exit(21);
    }

    if (!parameters->outFile) {
        size_t inFileLen = strlen(parameters->inFile);
        parameters->outFile = malloc(sizeof(char) * inFileLen + 7);
        strcpy(parameters->outFile, parameters->inFile);
        strcpy(parameters->outFile + inFileLen, ".out.c");
    }

    return parameters;
}

void clFree(clParameters* cl) {
    if (cl->inFile) {
        free(cl->inFile);
    }
    if (cl->outFile) {
        free(cl->outFile);
    }
    free(cl);
}

void clPrintUsage() {
    logMessage(
        "Utilisation: ib3m [\e[4mOPTION\e[0m...] \e[4mFILE\e[0m\n\n"
        "DESCRIPTION\n"
        "   ib3m permet de remplacer des paternes connus dans "
        "le fichier \e[4mFILE\e[0m par des appels de fonctions\n"
        "   potentiellement plus efficaces.\n\n"
        "OPTIONS\n"
        "   -version\n"
        "        Affiche les membres du groupe.\n"
        "   -tos\n"
        "        Affiche la table des symboles.\n"
        "   -ast\n"
        "        Affiche l'AST avant et après reconaissance des fonctions.\n"
        "   -o \e[4mFILE\e[0m\n"
        "        Ecrit le résultat dans le fichier \e[4mFILE\e[0m.\n"
        "   -h\n"
        "        Affiche ce message.\n"
    );
}

void clPrintVersion() {
    logMessage(
        "ib3m est le projet du module Compilation de M1 Informatique du "
        "groupe 1B3M composé de :\n"
        "   - Maxime Desgrandchamps (I3D)\n"
        "   - Baptiste Forest (I3D)\n"
        "   - Miguel Gervilla (I3D)\n"
        "   - Maxime Hohl (I3D)\n"
    );
}

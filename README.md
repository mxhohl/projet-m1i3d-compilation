Projet Compilation
==================

Ceci est le projet du module Compilation du Master I3D du groupe composé de
*Maxime Desgrandchamps*, *Baptiste Forest*, *Miguel Gervilla* et *Maxime Hohl*.

Utilisation
-----------

### Compiler le projet

On peut simplement compiler tout le projet en utilisant le commande `make` 
l'éxécutable est situé à la racine et porte le nom `compiler`.  
On peu nettoyer le fichiers intermédiaires de compilation avec la commande 
`make clean`.
Pour nettoyer tout les fichiers générés il faut utiliser la commande `make 
cleanall`.

### Générer la documentation

La documentation doit être générée à l'aide de le commande `make doc`. Pour 
pouvoir générer la documentation, [Doxygen](http://doxygen.nl) doit être 
installé.

Une fois générée, la documentation se trouve dans le dossier `doc`.

Participation au développement
------------------------------

### Créer sa branche
Chaque personne participant au développement doit avoir sa branche de 
développement. Pour ce faire, il faut utiliser la suite de commande `git 
checkout -b <nom>-dev` (ou laisser faire son editeur favoris).

### Ajouter un fichier source (.c)
Tout les fichiers source (en `.c`) doivent se trouver dans un dossier (ou
sous dossier) de `src`.
Le `Makefile` n'a pas besoin d'être modifié.

### Ajouter un fichier header (.h)
Tout les fichiers header (en `.h`) doivent se trouver dans un dossier (ou
sous dossier) de `include`.
Le `Makefile` n'a pas besoin d'être modifié.

Pour include un header, il ne faut pas le préfixer du dossier `include`. 
Par exemple, pour include le fichier `include/sousdossier/header.h` il faut
écrire `#include "sousdossier/header.h"`.

### Ajouter une dépendance
Pour ajouter des dépendances, il faut les ajouter dans le `Makefile` sur le
ligne `LDLIBS`. Par exemple, pour ajouter OpenGL en dépendance, la ligne 
`LDLIBS = -lm` du `Makefile` deviendrai `LDLIBS = -lm -lGL`.

### Documenter le code
La documentation doit se trouver dans les headers. Tout les fichiers qui 
doivent êtres inclus doivent commencer par l'entête suivante :

```C
/*!
 * \file <nom du fichier .h>
 * <Une description du contenus du fichier>
 */
```

Pour la documentation du code, on se basera sur le format 
[Doxygen](http://doxygen.nl/manual/docblocks.html) "Qt Style".

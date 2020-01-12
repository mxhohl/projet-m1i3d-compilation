Projet Compilation
==================

Ceci est le projet du module Compilation du Master I3D du groupe composé de
*Maxime Desgrandchamps*, *Baptiste Forest*, *Miguel Gervilla* et *Maxime Hohl*.

Rapport
------------

Le rapport se trouve dans le dossier `documents`. Il est nommé `rapport.pdf`.

Utilisation
-----------

### Compiler le projet

On peut simplement compiler tout le projet en utilisant le commande `make` 
l'éxécutable est situé à la racine et porte le nom `compiler`. Pour ne pas
avoir les symboles de debug, il faut utiliser `make MODE=release`.  
On peu nettoyer le fichiers intermédiaires de compilation avec la commande 
`make clean`.
Pour nettoyer tout les fichiers générés il faut utiliser la commande `make 
cleanall`.

### Générer la documentation

La documentation doit être générée à l'aide de le commande `make doc`. Pour 
pouvoir générer la documentation, [Doxygen](http://doxygen.nl) doit être 
installé.

Une fois générée, la documentation se trouve dans le dossier `doc`.

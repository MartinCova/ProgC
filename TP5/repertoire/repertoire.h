//
//  repertoire.h
//  TP5
//
//  Created by Martin Cova on 19/10/2022.
//

#ifndef repertoire_h
#define repertoire_h

#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

void lire_dossier(char *);

void lire_dossier_recursif_i(char *, int);

void lire_dossier_recursif(char *dossier);

void lire_dossier_iteratif_i(char *, int);

#endif /* repertoire_h */

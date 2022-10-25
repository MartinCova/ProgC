//
//  repertoire.c
//  TP5
//
//  Created by Martin Cova on 19/10/2022.
//

#include "repertoire.h"

int main(int argc, char **argv) {
    
    char command[256];
    printf("saisissez la commande à réaliser: ");
    scanf("%s", command);
//    if (argc < 2) {
//        printf("Usage: readdir path\n");
//        return(EXIT_FAILURE);
//    }
//    DIR *dirp = opendir(argv[1]);
//    if (dirp == NULL) {
//        perror("opendir");
//        return(EXIT_FAILURE);
//    }
    
    char *test = "/Users/martincova/Documents/Code/Progc";
    if(strcmp(command,"ls") == 0){
//        printf("1");
        lire_dossier(argv[1]);
    }
//    if(strcmp(command,"ls-R") == 0){
////        printf("2");
//        lire_dossier_recursif(argv[1]);
//    }
    if(strcmp(command,"ls-R") == 0){
//        printf("2");
        lire_dossier_iteratif_i(test, 0);
    }

return(0);
}


void lire_dossier(char *dossier){
    DIR *dirp = opendir(dossier);
   
    struct dirent * ent;
    while(dirp) {
        ent = readdir(dirp);
        if (ent == NULL) {
            break;
        }
        printf("%s \n", ent->d_name);
    }
    closedir(dirp);
}

void lire_dossier_recursif_i(char *dossier, int arbo_index){
//    printf("%s \n", dossier);
    DIR *dirp = opendir(dossier);
    char chemin[4096];
    struct dirent * ent;
    while((ent = readdir(dirp)) != 0){
        if (strcmp(ent->d_name, ".")!=0 && strcmp(ent->d_name, "..")!=0){
            for (int i = 0; i < arbo_index; i++) {
                printf("  ");
            }
            printf("%s \n", ent->d_name);
            if (ent->d_type == 0x4){ //signifie que c'est un répertoire
                strcpy(chemin, dossier);
                strcat(chemin,"/");
                strcat(chemin, ent->d_name);
                lire_dossier_recursif_i(chemin, arbo_index+1);
              }
        }
    }
    closedir(dirp);
}

void lire_dossier_recursif(char *dossier){
    lire_dossier_recursif_i(dossier, 0);
}

void lire_dossier_iteratif_i(char *dossier,int arbo_index){
    DIR *dirp = opendir(dossier);
    char chemin[4096];
    struct dirent * ent;
    while((ent = readdir(dirp)) != 0){
        if (strcmp(ent->d_name, ".")!=0 && strcmp(ent->d_name, "..")!=0){
            printf("%s \n", ent->d_name);
            while (ent->d_type == 0x4){ //signifie que c'est un répertoire
                strcpy(chemin, dossier);
                strcat(chemin,"/");
                strcat(chemin, ent->d_name);
                DIR *dirp = opendir(chemin);
                while((ent = readdir(dirp)) != 0){
                    if (strcmp(ent->d_name, ".")!=0 && strcmp(ent->d_name, "..")!=0){
                        for (int i = 0; i < arbo_index; i++) {
                            printf("  ");
                        }
                        printf("%s \n", ent->d_name);
                    }
                }
            }
        }
    }
    closedir(dirp);
}

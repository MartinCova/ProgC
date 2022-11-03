//
//  main.c
//  test
//
//  Created by Martin Cova on 30/10/2022.
//

#include <stdio.h>
#include "main.h"
#include <string.h>
#include <stdlib.h>

#define TAILLE_MAX 1000
 
typedef struct json_TP6 {
    char *str;
    struct{
        char *code;
        char *val;
    };
} Json;


int fsize(const char * fname, long * ptr)
{
    /* Cette fonction retourne 0 en cas de succès, une valeur différente dans le cas contraire. */
    FILE * f;
    int ret = 0;
    f = fopen(fname, "rb");
    if (f != NULL)
    {
        fseek(f, 0, SEEK_END);  /* aller à la fin du fichier */
        *ptr = ftell(f);        /* lire l'offset de ptr par rapport au début du fichier */
        fclose(f);
    }
    else
        ret = 1;
    return ret;
}


void get_commande(Json *instruction){
    char *str_copy = malloc(strlen(instruction->str));
    strcpy(str_copy, instruction->str);
    char delim = ',';
    char *save_str;
    char *code = strtok_r(str_copy, &delim, &save_str);
    char *val = malloc(sizeof(save_str));
    val = save_str;
    instruction->code = code+13;
    instruction->val = val+15;
}


int main(void)
{
    char *path = "/Users/martincova/Documents/Code/Progc/TP5/test/test.json";
    
    long size_of_file = 0;
    long *size_of_file_ptr = &size_of_file;
    if(fsize(path, size_of_file_ptr) !=0){// on récupère la taille du fichier
        return EXIT_FAILURE;
    }
    char chaine[size_of_file];  // allocation d'un tableau de la taille du fichier
    
    FILE* fichier;
    fichier = fopen(path, "r");
    if (fichier != NULL)
    {
        fread(chaine, size_of_file, 1, fichier);
        fclose(fichier);
    }
    else{
        return 1;
    }
    
    char delim_commande = '}';
    int i = 0;
    int nb_instrcution= 0;               // stocke le nombre d'instructions dans le json
    while(*(chaine+i) != '\0'){
        if(*(chaine+i) == delim_commande){
            nb_instrcution++;
        }
        i++;
    }
    Json instruction[3];
    
    char delim[] = "}";
    char *save_str;
    char *ptr_instruction = strtok_r(chaine, delim, &save_str);
    instruction[0].str = ptr_instruction;
    get_commande(&instruction[0]);
    for(int i = 1; i< nb_instrcution; i++){
        ptr_instruction = strtok_r(save_str, delim, &save_str);
        instruction[i].str = ptr_instruction+2;
        get_commande(&instruction[i]);
    }
    return 0;
}

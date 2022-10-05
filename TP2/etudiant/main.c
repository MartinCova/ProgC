//
//  main.c
//  etudiant
//
//  Created by Martin Cova on 29/09/2022.
//

#include <stdio.h>

short choose(char name[5][30]){
    printf("quel personne voulez vous ?:  \n");
    short num_choose;
    for(int i = 0;i < 5; i++ ){
        printf("%d : %s \n",i,  *(name+i));
    }
    printf("votre réponse ici : ");
    scanf("%hd", &num_choose );
    return num_choose;
}

void afficher_eleve(char name[5], char surname[5], char adresse[5],
                    short note1, char note2){
    printf("nom: %s, prenom: %s, adresse: %s, progc: %hd, syst exploitation: %hd \n ", name, surname, adresse, note1, note2);
    
}



int main() {
    char name[5][30] = {"jo","jack","john","jami","gluck"};
    char surname[5][30] = {"a","b","c","d","e"};
    char adresse[5][30] = {"paris","lyon","marseille","toulouse","bordeaux"};
    short note1[5] = {10,12,15,16,18};
    short note2[5] = {0,2,5,6,8};
    char choix[] = "";

    short num_choose = choose(name);
    
    afficher_eleve(*(name +num_choose), *(surname +num_choose), *(adresse +num_choose),
                   *(note1 +num_choose),
                   *(note2 +num_choose));
    
    return 0;
    
}

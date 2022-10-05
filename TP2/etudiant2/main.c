//
//  main.c
//  etudiant2
//
//  Created by Martin Cova on 30/09/2022.
//

#include <stdio.h>
#include <string.h>

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

int main() {
    struct etudiant{
        char name[30];
        char surname[30];
        char adresse[30];
        short note1;
        short note2;
    };
    
    struct etudiant etudiant_test[5];
    
    strcpy(etudiant_test[0].name, "jo");
    strcpy(etudiant_test[0].surname, "a");
    
    printf("%s", etudiant_test[0].name);
    
    return 0;
}

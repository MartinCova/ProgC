//
//  main.c
//  etudiant2
//
//  Created by Martin Cova on 30/09/2022.
//

#include <stdio.h>
#include <string.h>

struct etudiant{
       char name[30];
       char surname[30];
       char adresse[30];
       short note1;
       short note2;
   };

short choose(struct etudiant *ptr_tab ){
    printf("quel personne voulez vous ?:  \n");
    short num_choose;
    for(int i = 0;i < 5; i++ ){
        printf("%d : %s \n",i,  (ptr_tab+i)->name);
    }
    printf("votre réponse ici : ");
    scanf("%hd", &num_choose );
    return num_choose;
}

void afficher_eleve(struct etudiant *ptr_struct){
    printf("nom: %s, prénom: %s, adresse: %s, progc: %hd, syst exploitation: %hd \n", (*ptr_struct).name, (*ptr_struct).surname, (*ptr_struct).adresse, (*ptr_struct).note1, (*ptr_struct).note2);


}


int main() {
       
    struct etudiant etudiant_test[5];
    
    strcpy(etudiant_test[0].name, "jo");
    strcpy(etudiant_test[0].surname, "a");
    strcpy(etudiant_test[0].adresse, "paris");
    etudiant_test[0].note1 = 10;
    etudiant_test[0].note1 =  0;
    
    strcpy(etudiant_test[1].name, "jack");
    strcpy(etudiant_test[1].surname, "b");
    strcpy(etudiant_test[1].adresse, "lyon");
    etudiant_test[1].note1 = 12;
    etudiant_test[1].note1 =  2;
    
    strcpy(etudiant_test[2].name, "john");
    strcpy(etudiant_test[2].surname, "c");
    strcpy(etudiant_test[2].adresse, "marseille");
    etudiant_test[2].note1 = 15;
    etudiant_test[2].note1 =  5;
    
    strcpy(etudiant_test[3].name, "jami");
    strcpy(etudiant_test[3].surname, "d");
    strcpy(etudiant_test[3].adresse, "toulouse");
    etudiant_test[3].note1 = 17;
    etudiant_test[3].note1 =  7;
    
    strcpy(etudiant_test[4].name, "gluck");
    strcpy(etudiant_test[4].surname, "e");
    strcpy(etudiant_test[4].adresse, "bordeaux");
    etudiant_test[4].note1 = 18;
    etudiant_test[4].note1 =  8;
    
    afficher_eleve(&etudiant_test[choose(etudiant_test)]);
    
    return 0;
}

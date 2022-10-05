//
//  main.c
//  chaine
//
//  Created by Martin Cova on 28/09/2022.
//

#include <stdio.h>
#include <stdlib.h>

void copy(char *mess, char *mess_copy){
    for (int i = 0; i<= *mess +1; i++){
        *(mess_copy +i) = *(mess+i);
    }

}

int count(char *mess){
    int cpt =0;
    for ( ; *mess; mess++){
        cpt = cpt+1;
    }
    return cpt;
    
}

void conca(char *mess1, char *mess2, char *conca){
    int i = 0;
    for (; *mess1 ; mess1++,i++){
        *(conca+i) = *(mess1);
    }
    for (;*mess2;mess2++, i++){
        *(conca + count(mess1) +i) = *mess2;
    }
}



int main() {
    char *mess1 = "message----";
    char *mess2 = "message2----";
    
//    char mess3[] = "message";
//
//
//    printf("%lu", sizeof(mess3));

    char *mess_copy = malloc(sizeof(*mess1));
    copy(mess1, mess_copy);
    printf("taille de la chaine: %d \n",count(mess_copy));
    printf("message copié: %s \n \n", mess_copy);

    char *conc = malloc(count(mess1)+ count(mess2));
        conca(mess1,mess2, conc);
        printf("message concaténé : %s \n", conc);
    printf("%d \n", count(conc));
    
    return 0;
}

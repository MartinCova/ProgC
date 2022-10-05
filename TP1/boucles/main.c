//
//  main.c
//  boucles
//
//  Created by Martin Cova on 21/09/2022.
//

#include <stdio.h>

int main() {
    short compteur;
    printf("taille du triangle : ");
    scanf("%hd",&compteur);
    short a = 3;
    short i = 0;
    short j = 0;
    switch (a) {
        case 1:
            for (i =0; i< compteur-1; i++) {
                printf("*");
                if(i>=1){
                    for (j =0; j< i - 1; j++) {
                                printf("#");
                            }
                    printf("*");
                }
                printf("\n");
            }
            for (i =0; i< compteur; i++) {
                printf("*");
            }
            printf("\n");
            break;
        case 2:
            while (i< compteur) {
                printf("*");
                if(i>=1){
                    for (j =0; j< i - 1; j++) {
                                printf("#");
                            }
                    printf("*");
                }
                i++;
                printf("\n");
            }
        case 3:
            do{
                printf("*");
                if(i>=1){
                    for (j =0; j< i - 1; j++) {
                                printf("#");
                            }
                    printf("*");
                }
                i++;
                printf("\n");
            }while(i< compteur);
            break;
        default:
            break;
    }
    return 0;
}

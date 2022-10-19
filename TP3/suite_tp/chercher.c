//
//  chercher.c
//  suite_tp
//
//  Created by Martin Cova on 15/10/2022.
//

#include "chercher.h"

#define SIZE_TAB 50

int chercher(void){
    
    int tab[SIZE_TAB] = {};
    int *ptrtab = &tab[0];
    
    int_tab_random(ptrtab, SIZE_TAB);
    
    for(int i =0; i< SIZE_TAB; i++){
        printf("%d \n", *(ptrtab+i));
    }
    
    int val_to_search;
        printf("valeur à chercher : ");
        scanf("%d", &val_to_search);
        
    for(int i =0; i< SIZE_TAB; i++){
        printf("%d \n", *(ptrtab+i));
        if(*(ptrtab+i) == val_to_search){
            printf("entier présent \n");
            return 0;
        }
    }
    printf("entier non présent\n");
    return 0;
}

//
//  main.c
//  tri
//
//  Created by Martin Cova on 14/10/2022.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "malib.h"

#define SIZE_TAB 100

//int gen_random(int max){
//    int result;
//    result = rand() % max;
//    return result;
//}
//void int_tab_random(int *ptrtab, int size_tab){
//    for(int i =0; i< size_tab; i++){
//        *(ptrtab+i) = gen_random(0xffff);
//    }
//}


int main() {
    time_t t;
    srand((unsigned)time(&t));
    
    int tab[SIZE_TAB] = {};
    int *ptrtab = &tab[0];
    
    int_tab_random(ptrtab, SIZE_TAB);
    
    for(int i =0; i< SIZE_TAB; i++){
        printf("%d \n", *(ptrtab+i));
    }
    
    
    printf("------------------------\n");
    
    triRapid(tab, 0, SIZE_TAB-1);
    
    for(int i =0; i< SIZE_TAB; i++){
        printf("%d \n", *(ptrtab+i));
    }

    
    
    return 0;
}


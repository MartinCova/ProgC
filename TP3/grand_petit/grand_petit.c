//
//  main.c
//  grand_petit
//
//  Created by Martin Cova on 05/10/2022.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SIZE_TAB 100

int __gen_random(int max){
    int result;
    result = rand() % max;
    return result;
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    
    int tab[100] = {};
    int *ptrtab = &tab[0];
    
    for(int i =0; i< SIZE_TAB; i++){
        *(ptrtab+i) = __gen_random(0xffff);
    }
    int val_min = tab[0];
    int val_max = tab[0];
    
    for(int i =1; i< SIZE_TAB; i++){
        if(*(ptrtab+i) < val_min){
            val_min = *(ptrtab+i);
        }
        if(*(ptrtab+i) > val_max){
            val_max = *(ptrtab+i);
        }
    }
    
    
    for(int i =0; i< SIZE_TAB; i++){
        printf("%d \n", *(ptrtab+i));
    }
    
    printf("val min = %d \n", val_min);
    printf("val min = %d \n", val_max);
    
    
    
    return 0;
}

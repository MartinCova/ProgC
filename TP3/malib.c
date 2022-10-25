//
//  chercher.c
//  TP3
//
//  Created by Martin Cova on 15/10/2022.
//

#include "malib.h"


void permuter(int *a, int *b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void triRapid(int tab[], int first, int last) {
    int pivot, i, j;
    if(first < last) {
        pivot = first;
        i = first;
        j = last;
        while (i < j) {
            while(tab[i] <= tab[pivot] && i < last)
                i++;
            while(tab[j] > tab[pivot])
                j--;
            if(i < j) {
                permuter(&tab[i], &tab[j]);
            }
        }
        permuter(&tab[pivot], &tab[j]);
        triRapid(tab, first, j - 1);
        triRapid(tab, j + 1, last);
    }
}


int gen_random(int max){
    int result;
    result = rand() % max;
    return result;
}


void int_tab_random(int *ptrtab, int size_tab){
    int val_max;
    printf("entrez la valeur max à générer : ");
    scanf("%d", &val_max);
    for(int i =0; i< size_tab; i++){
        *(ptrtab+i) = gen_random(val_max);
    }
}

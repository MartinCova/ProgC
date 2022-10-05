//
//  main.c
//  conditions
//
//  Created by Martin Cova on 21/09/2022.
//

#include <stdio.h>

int main() {
    short a = 0;
    short val_max = 1000;
    short count2 = 0;
    short count103 = 0;
    short count5 = 0;
    
    for (a = 0; a<= val_max; a++) {
        if( a%15 ==0 && a%2 ==0){
            printf("%d est divisible par 2 et 15 \n",a);
            count2++;
        }
        if(a%103 ==0 | a%107==0){
            printf("%d est divisible par 103 ou 107\n", a);
            count103++;
        }
        if( (a%5 ==0 | a%7 ==0) & (a%3!=0)){
            printf("%d est divisible par 5 ou 7 mais pas par 3 \n",a);
            count5++;
        }
    
    }
    printf("nb divisible par 2 et 15 : %d \n", count2);
    printf("nb divisible par 103 et 107 : %d \n", count103);
    printf("nb divisible par 5 ou 7 : %d \n", count5);
    return 0;
}

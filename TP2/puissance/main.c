//
//  main.c
//  puissance
//
//  Created by Martin Cova on 28/09/2022.
//

#include <stdio.h>

int main() {
//    short a;
    short a;
    printf("variable: ");
    scanf("%hd",&a);
    short b;
    printf("puissance: ");
    scanf("%hd",&b);
    char i = 0;
    short c = a;
    for(i = 0;i< b-1; i++){
        c = c*a;
    }
    printf("valeur: %hd \n", c);
}



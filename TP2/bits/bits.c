//
//  main.c
//  bits
//
//  Created by Martin Cova on 28/09/2022.
//

#include <stdio.h>

short verify_bit(int n){
//    printf("%d", sizeof(n));
    return (((n >> 28) & 1) && ((n >> 12) & 1));
}

int main() {
    int d;
    printf("entrez un nombre :");
    scanf("%d", &d);
    printf("\n");
    printf("val : %hd \n", verify_bit(d));
    
}


//
//  main.c
//  sizeof_types
//
//  Created by Martin Cova on 21/09/2022.
//

#include <stdio.h>

int main() {
    printf("taille des char\n");
    printf("%lu\n", sizeof(char));
    printf("%lu\n", sizeof(unsigned char));
    printf("taille des short\n");
    printf("%lu\n", sizeof(short));
    printf("%lu\n", sizeof(unsigned short));
    printf("taille des int\n");
    printf("%lu\n", sizeof(int));
    printf("%lu\n", sizeof(unsigned int));
    printf("taille des long int\n");
    printf("%lu\n", sizeof(long int));
    printf("%lu\n", sizeof(unsigned long int));
    printf("taille des long long int\n");
    printf("%lu\n", sizeof(long long int));
    printf("%lu\n", sizeof(unsigned long long int));
    printf("taille des float\n");
    printf("%lu\n", sizeof(float));
    printf("taille des double\n");
    printf("%lu\n", sizeof(double));
    printf("%lu\n", sizeof(long double));
    return 0;
}


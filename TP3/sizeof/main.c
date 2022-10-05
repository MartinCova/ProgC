//
//  main.c
//  sizeof
//
//  Created by Martin Cova on 05/10/2022.
//

#include <stdio.h>

int main() {
    printf(" sizeof(int) = %lu \n", sizeof (int));
    printf("%lu \n", sizeof (int *));
    printf("%lu \n", sizeof (int**));
    printf("%lu \n", sizeof (char));
    printf("%lu \n", sizeof (char*));
    printf("%lu \n", sizeof (char**));
    printf("%lu \n", sizeof (char***));
    printf("%lu \n", sizeof (float));
    printf("%lu \n", sizeof (float*));
    printf("%lu \n", sizeof (float**));
    printf("%lu \n", sizeof (float***));
    return 0;
}

//
//  main.c
//  variables
//
//  Created by Martin Cova on 21/09/2022.
//

#include <stdio.h>

int main(){
    char my_char = 'c';
    printf("%c\n", my_char);
    
    unsigned char my_unsigned_char = 234;
    printf("%hhu\n", my_unsigned_char);
    
    unsigned int my_int = 42949672;
    printf("%u\n", my_int);
    
    long int my_long_int = 888888;
    printf("long int: %ld\n", my_long_int);
    
    return 0;
}

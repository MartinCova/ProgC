//
//  main.c
//  opérateurs
//
//  Created by Martin Cova on 21/09/2022.
//

#include <stdio.h>

int main() {
    signed short a = 16;
    signed short b = 3;
    short c = a*b;
    short d = a+b;
    short e = a-b;
    short f = a>b;
    short g = !b;
    printf("multiplication: %hd \n",c);
    printf("addition: %hd \n",d);
    printf("soustraction: %hd \n",e);
    printf("a plus petit: %hd \n",f);
    printf("a ou b: %hd \n",g);
// ...  
    return 0;
}

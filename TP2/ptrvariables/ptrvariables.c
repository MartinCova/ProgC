//
//  main.c
//  ptrvariables
//
//  Created by Martin Cova on 12/10/2022.
//

#include <stdio.h>

void __printHexa(void* variable, int size){
  // printf("%d\n", sizeof(*variable));
  unsigned char *ptrChar = variable + size;
  for (int i = size; i > 0; i--) {
    ptrChar--;
    printf("%02x ", *ptrChar);
  }
   printf("\n");
}

int main() {
    int varInt = 0xa47865ff;
    printf("i: ");
    __printHexa(&varInt, sizeof(varInt));
    
    float varFloat = 2;
    printf("f: ");
    __printHexa(&varFloat, sizeof(varFloat));
    
    short varShort = 32;
    printf("s: ");
    __printHexa(&varShort, sizeof(varShort));
    
    long int varLongInt = 0x87999577f42603;
    printf("li: ");
    __printHexa(&varLongInt, sizeof(varLongInt));
    
    double varDouble = 7646.45556;
    printf("d: ");
    __printHexa(&varDouble, sizeof(varDouble));
    
    
    return 0;
}

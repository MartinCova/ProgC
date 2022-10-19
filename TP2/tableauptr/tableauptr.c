//
//  main.c
//  tableauptr
//
//  Created by Martin Cova on 12/10/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int tableauInt[10] = {};
    int *ptrInt = &tableauInt[0];
    
    float tableauFloat[10] = {};
    float *ptrFloat = &tableauFloat[0];
    
    for (short i = 0; i < 10; i++) {
        
        *(ptrInt+i)= rand()%(0xffffff);
        *(ptrFloat+i) = rand()*0.0000033f;
        printf("Int n°%hu: %d\n",i,*(ptrInt+i));
        printf("Float n°%hu: %f\n",i,*(ptrFloat+i));
    }
    
    for (short i = 0; i< 10; i++){
        if( i %2 == 0){
            *(ptrInt+i) = *(ptrInt+i)*3;
            *(ptrFloat+i) = *(ptrFloat+i)*3;
        }
        printf("Int n°%hu: %d\n",i,*(ptrInt+i));
        printf("Float n°%hu: %f\n",i,*(ptrFloat+i));
    }

    return 0;
}

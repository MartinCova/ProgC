//
//  main.c
//  couleurs
//
//  Created by Martin Cova on 05/10/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct couleur{
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };
    
void init(struct couleur *ptr_color){
    srand((unsigned)time(NULL));
    
    for(int i = 0; i<10; i++){
        (ptr_color +i)->r = rand()%(255+1);
        (ptr_color +i)->g = rand()%(255+1);
        (ptr_color +i)->b = rand()%(255+1);
        (ptr_color +i)->a = rand()%(255+1);
        
        printf("r=%#x, g=%#x, b=%#x, a=%#x \n", (ptr_color+i)->r, (ptr_color+i)->g, (ptr_color+i)->b, (ptr_color+i)->b);
    }
    
//    printf("%#x \n", colors[0].r);
    
}


int main() {
    srand((unsigned)time(NULL));
    
    struct couleur colors[10];
    
    init(colors);
    return 0;
}

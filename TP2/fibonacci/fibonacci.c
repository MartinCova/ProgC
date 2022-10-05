//
//  main.c
//  fibonacci
//
//  Created by Martin Cova on 28/09/2022.
//

#include <stdio.h>

void fibonacci(int U0,int U1,int n){
    printf("U0 = %d , U1 = %d ,", U0,U1);
    for (int i = 2; i<n +1; i ++){
        int Un = U0 +U1;
        printf("U%d = %d , ", i, Un);
        U0 = U1;
        U1 = Un;
    }
    
}


int main() {
    int n ;
    printf("rentre une valeur chacal: ");
    scanf("%d", &n);
    int u0 = 0;
    int u1 = 1;
    if (n < 2){
        printf("t'es con \n");
        main();
    }
    else{
        fibonacci(u0, u1, n);
    }
}

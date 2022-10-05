#include <stdio.h>
#include <math.h>

int main() {
    float rayon;
    printf("quel rayon voulez vous ? ");
    scanf("%f", &rayon);
    printf("l'aire du cercle est de %f\n",M_PI*rayon*rayon);
    printf("le rayon du cercle est de %f\n",M_PI*rayon*2);
    return 0;
}


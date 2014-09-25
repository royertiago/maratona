/* A.cpp
 * Problema da etapa regional da maratona de 2014
 */
#include <stdio.h>

int main() {
    int x, y;
    scanf( "%d %d", &x, &y );
    printf( "%d\n", (2*y - x - 1)/(y - x) );
    return 0;
}

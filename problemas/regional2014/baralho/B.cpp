/* B.cpp
 * Problema da etapa regional da maratona de 2014
 */
#include <stdio.h>

unsigned solve( unsigned size ) {
    unsigned p = 2, i = 1;
    while( p != 1 ) {
        p = (p * 2) % (size + 1);
        ++i;
    }
    return i;
}

int main() {
    unsigned size;
    scanf( "%d", &size );
    printf( "%d\n", solve(size) );
    return 0;
}

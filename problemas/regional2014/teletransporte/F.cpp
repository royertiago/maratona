/* F.cpp
 * Problema da etapa regional da maratona de 2014.
 */
#include <stdio.h>

unsigned N, V; // naves/viagens

unsigned g[100][100], aux[100][100];
void mult( unsigned target[100][100], unsigned source[100][100] ) {
    static unsigned alce[100][100];
    for( unsigned i = 0; i < N; ++i )
        for( unsigned j = 0; j < N; ++j ) {
            alce[i][j] = 0;
            for( unsigned k = 0; k < N; ++k )
                alce[i][j] = (alce[i][j] + target[i][k]*source[k][j]) %10000;
        }
    for( unsigned i = 0; i < N; ++i )
        for( unsigned j = 0; j < N; ++j )
            target[i][j] = alce[i][j];
}

void expo( unsigned n ) {
    for( unsigned i = 0; i < N; ++i )
        for( unsigned j = 0; j < N; ++j )
            aux[i][j] = i == j;

    while( n != 0 ) {
        if( n % 2 == 1 )
            mult( aux, g );
        mult( g, g );
        n >>= 1;
    }
}

int main() {
    scanf( "%u %u", &N, &V );
    unsigned origem, destino;
    scanf( "%u %u", &origem, &destino );
    unsigned A, B, C, D;
    for( unsigned i = 0; i < N; ++i )
        for( unsigned j = 0; j < N; ++j )
            g[i][j] = 0;

    for( unsigned i = 0; i < N; ++i ) {
        scanf( "%u%u%u%u", &A, &B, &C, &D );
        g[i][A-1]++;
        g[i][B-1]++;
        g[i][C-1]++;
        g[i][D-1]++;
    }

    expo( V );
    printf( "%u\n", aux[origem-1][destino-1] );
}

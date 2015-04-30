#include <stdio.h>

int main() {
    int E, F;
    int fila[1000000];
    while( scanf( "%d", &E ) != EOF && E != 0 ) {
        for( int i = 0; i < E; i++ )
            fila[i] = 0;
        scanf( "%d", &F );
        for( int i = 0; i < F; i++ ) {
            int j;
            scanf( "%d", &j );
            fila[j]++;
        }
        int soma = 0;
        printf( "0" );
        for( int i = 1; i < E; i++ ) {
            /* Não precisamos ir até o índice E pois não existem estudantes
             * atrás do E-ésimo.
             */
            soma += fila[i];
            printf( " %d", soma );
        }
        printf( "\n" );
    }
    return 0;
}

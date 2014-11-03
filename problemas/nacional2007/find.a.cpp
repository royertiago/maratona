/* find.a.cpp
 * Problema F da etapa nacional da Maratona de 2007.
 */
#include <stdio.h>

#define MAX 300
int R, C, K;
char seat[MAX][MAX+1]; // MAX+1 para armazenar o '\0'

int min( int i, int j ) { return i < j ? i : j; }

/* Retorna o comprimento da menor sequência contígua de elementos
 * cuja soma é maior ou igual a K, ou MAX*MAX caso nenhuma tal
 * sequência exista. line deve ser uma sequência contígua de linhas
 * da matriz original de assentos, compactada para conter apenas
 * o número de elementos em cada coluna. */
int solve( int * line ) {
    int best = MAX*MAX;
    int i = 0, j = 0; // Representam o intervalo [i, j)
    int sum = 0;
    while( j < C ) {
        while( sum < K && j < C )
            sum += line[j++];
        while( sum >= K ) {
            best = min( j - i, best );
            sum -= line[i++];
        }
    }
    return best;
}

int solve() {
    int buffer[MAX];
    int best = MAX * MAX;
    for( int i = 0; i < R; ++i ) {
        for( int k = 0; k < C; k++ )
            buffer[k] = 0;

        for( int j = i; j < R; ++j ) {
            /* i e j representam o intervalo de colunas [i, j]. Note que aqui
             * o intervalo é fechado.
             * Invariante: no início de cada iteração, buffer[k] contém o
             * número de cadeiras livres na coluna k nas linhas [i, j). */
            for( int k = 0; k < C; ++k )
                buffer[k] += (seat[j][k] == '.');
            best = min( best, solve(buffer) * (j - i + 1) );
        }
    }
    return best;
}

int main() {
    while( scanf("%d%d%d", &R, &C, &K) != EOF && R != 0 ) {
        for( int i = 0; i < R; ++i )
            scanf( "%s", &seat[i][0] );
        printf( "%d\n", solve() );
    }
    return 0;
}

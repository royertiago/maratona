/* find.b.cpp
 * Problema F da etapa nacional da Maratona de 2007.
 *
 * Este arquivo implementa essencialmente a mesma solução de find.a.cpp, mas
 * usando somas parciais ao invés de um vetor buffer.
 */
#include <stdio.h>

#define MAX 300
int R, C, K;
char seat[MAX][MAX+1]; // MAX+1 para armazenar o '\0'
int partials[MAX+1][MAX];
// partials[i][j] contém a soma dos elementos na coluna j nas linhas [0, i).

int min( int i, int j ) { return i < j ? i : j; }

struct state {
    int i, j;
    int col( int k ) {
        return partials[j+1][k] - partials[i][k];
    }
    int solve() {
        int best = MAX*MAX;
        int a = 0, b = 0;
        int sum = 0;
        while( b < C ) {
            while( sum < K && b < C )
                sum += col(b++);
            while( sum >= K ) {
                best = min( b - a, best );
                sum -= col(a++);
            }
        }
        return best * (j - i + 1);
    }
    /* Coloquei numa struct apenas para minimizar o esforço de cofificar
     * a função col(k). */
};

int solve() {
    for( int k = 0; k < C; ++k )
        partials[0][k] = 0;
    for( int i = 0; i < R; ++i )
        for( int k = 0; k < C; ++k )
            partials[i+1][k] = partials[i][k] + (seat[i][k] == '.');

    state s = {0, 0};
    int best = MAX*MAX;

    for( ; s.i < R; s.i++ )
        for( s.j = s.i; s.j < R; s.j++ )
            best = min( best, s.solve() );
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

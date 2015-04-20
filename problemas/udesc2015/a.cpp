/* Problema A da seletiva doméstica da UDESC de 2015.
 *
 * Algoritmo de Floyd-Warshall. Complexidade: n^3.
 */
#include <stdio.h>
#include <algorithm>
#include <limits.h>

#define INF (INT_MAX/4)

int c[100][100];
int m, n;

void floyd_warshall() {
    for( int k = 0; k < n; k++ )
        for( int i = 0; i < n; i++ )
            for( int j = 0; j < n; j++ )
                c[i][j] = std::min(c[i][j], c[i][k] + c[k][j]);
}

int main() {
    while( scanf("%d %d", &n, &m) == 2 && m != 0 && n != 0 ) {
        for( int i = 0; i < n; i++ )
            for( int j = 0; j < n; j++ )
                c[i][j] = INF;
        for( int i = 0; i < n; i++ )
            c[i][i] = 0;

        for( int i = 0; i < m; i++ ) {
            int a, b, d;
            scanf( "%d %d %d", &a, &b, &d );
            c[a][b] = d;
            c[b][a] = d;
        }
        int k;
        scanf( "%d", &k );
        for( int i = 0; i < k; i++ ) {
            int a, b;
            scanf( "%d %d", &a, &b );
            c[a][b] = INF;
            c[b][a] = INF;
        }
        floyd_warshall();
        int q;
        scanf( "%d", &q );
        for( int i = 0; i < q; i++ ) {
            int a, b;
            scanf( "%d %d", &a, &b );
            printf( "%d\n", c[a][b] == INF ? -1 : c[a][b] );
        }
    }
    return 0;
}

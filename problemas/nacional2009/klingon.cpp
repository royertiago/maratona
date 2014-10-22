/* klingon.cpp
 * Problema K da etapa regional da Maratona de 2009.
 */
#include <stdio.h>
#include <algorithm>

int N, T; // Number of divisions and limit.
#define SENTINEL 1001

struct divisions_t {
    int * data;
    int l, r; // Number of students to the left and to the right of the limit.
    // The limit is inclusive to l and exclusive to r.

    /* Update l and r according to the new T (that is assumed to be greater
     * than previous T) and returns the diffence between them. */
    int advance() {
        while( *data <= T ) {
            ++data; --l; ++r;
        }
        return l < r ? r - l : l - r;
    }
} division[10*1000];

int data[100*1000 + 10*1000];

int main() {
    while( scanf("%d", &N) != EOF && N != 0 ) {
        int * d = data;
        int n;
        for( int i = 0; i < N; ++i ) {
            scanf( "%d", &n );
            for( int j = 0; j < n; ++j )
                scanf( "%d", &d[j] );
            d[n] = SENTINEL;
            division[i] = {d, n, 0};
            std::sort( d, d+n );
            d += n+1;
        }
        int best = 100*1000+1;
        for( T = 0; T < SENTINEL; ++T ) {
            int sum = 0;
            for( int i = 0; i < N; ++i )
                sum += division[i].advance();
            best = best < sum ? best : sum;
        }
        printf( "%d\n", best );
    }
    return 0;
}

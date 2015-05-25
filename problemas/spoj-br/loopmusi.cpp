/* Problema: http://br.spoj.com/problems/LOOPMUSI/
 *
 * We will simulate a finite automaton to compute the number of peaks.
 * The state is boolean;
 * true means the magnitude increased from the last point to the current
 * and false means the magnitude decreased.
 *
 * Eack peak will only be counted in the point the it happens.
 * state always refer to the slope between H[i-1] and H[i];
 * to discover the next slope, we compare H[i] and H[i+1].
 * At this point we make use of the fact that
 * the problem guarantees that H[i] != h[i+1],
 * so we do not need to care about the case H[i] == H[i+1].
 */
#include <stdio.h>

int H[(int)1e4 + 1];
int N;

int solve() {
    int count = 0;
    bool state = H[N-1] < H[0];
    H[N] = H[0];
    for( int i = 0; i < N; i++ )
        if( (H[i] < H[i+1]) != state ) {
            state = H[i] < H[i+1];
            count++;
        }

    return count;
}

int main() {
    while( scanf("%d", &N) != EOF && N != 0 ) {
        for( int i = 0; i < N; i++ )
            scanf( "%d", &H[i] );
        printf( "%d\n", solve() );
    }
    return 0;
}

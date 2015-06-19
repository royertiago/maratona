#include <algorithm>
#include <stdio.h>

#define INF (int) 1e9

int f[180], p[180], h[180], d[180];
int n;

/* pd[i] is the solution for days [i, ..., n-1]
 * starting with stock 0.
 */
int pd[181];

/* ds[i] = sum_{k=i}^{n-1} d[i]
 * That is, it's the remaining demand.
 */
int ds[181];

int solve() {
    // Precomputation
    ds[n] = 0;
    for( int i = n-1; i >= 0; i-- ) {
        ds[i] = d[i] + ds[i+1];
    }

    pd[n] = 0;
    for( int i = n-1; i >= 0; i-- ) {
        pd[i] = INF;
        // We will solve pd[i].
        for( int j = 1; i + j <= n; j++ ) {
            /* We will try to produce enough for this
             * and the next j-1 days.
             */
            int stock = ds[i] - ds[i+j];
            int cost = f[i] + p[i] * stock + pd[i+j];
            for( int k = 0; k < j; k++ ) {
                // This could be optimized, but n <= 180, so...
                stock -= d[i+k];
                cost += h[i+k]*stock;
            }
            pd[i] = std::min(pd[i], cost);
        }
    }
    return pd[0];
}

int main() {
    int i = 1;
    while( scanf( "%d", &n ) != EOF && n != 0 ) {
        for( int i = 0; i < n; i++ )
            scanf( "%d%d%d%d", &f[i], &p[i], &h[i], &d[i] );

        printf( "Instancia #%d\n%d\n\n", i++, solve() );
    }
    return 0;
}

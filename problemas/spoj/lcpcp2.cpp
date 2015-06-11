/* Problem: http://www.spoj.com/problems/LCPCP2/
 * Modular exponentiation.
 */
#include <stdio.h>

int solve( long long b, long long e, int m ) {
    long long int r = 1;
    while( e != 0 ) {
        if( e % 2 == 1 )
            r = r * b % m;
        b = b * b % m;
        e >>= 1;
    }
    return r;
}

int main() {
    int t;
    scanf( "%d", &t );
    for( int i = 1; i <= t; i++ ) {
        long long b, e, m;
        scanf( "%lld%lld%lld", &b, &e, &m );
        printf( "%d. %d\n", i, solve(b, e, m) );
    }
    return 0;
}

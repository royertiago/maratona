/* Problem: http://www.spoj.com/problems/RABBIT1/
 * Modular exponentiation.
 */
#include <stdio.h>

struct fib {
    long long m[2][2];
};
int m, n;
fib operator *( fib a, fib b ){
    fib c = {0};
    for( int i = 0; i < 2; i++ )
    for( int j = 0; j < 2; j++ )
    for( int k = 0; k < 2; k++ )
        c.m[i][j] = (c.m[i][j] + a.m[i][k]*b.m[k][j]) % (1 << m);
    return c;
}

int solve() {
    fib e = {1, 1, 1, 0};
    fib r = {1, 0, 0, 1};
    while( n != 0 ) {
        if( n % 2 == 1 )
            r = r * e;
        e = e * e;
        n >>= 1;
    }
    return r.m[0][0];
}

int main() {
    int t;
    scanf( "%d", &t );
    while( t-- ) {
        scanf( "%d%d", &n, &m );
        printf( "%d\n", solve() );
    }
    return 0;
}

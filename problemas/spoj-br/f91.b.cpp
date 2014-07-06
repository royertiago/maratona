/* f91.b.cpp
 * Problema http://br.spoj.com/problems/F91/
 * Esta solução usa stdio.h, e é aceita.
 */
#include <stdio.h>

int f91( int n ) {
    if( n < 101 )
        return 91;

    return n - 10;
}

int main() {
    int n;
    while( scanf("%d", &n) && n != 0 )
        printf( "f91(%i) = %i\n", n, f91(n) );
    return 0;
}

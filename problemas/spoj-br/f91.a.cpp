/* f91.a.cpp
 * Problema http://br.spoj.com/problems/F91/
 * Esta solução usa stdio.h, e é aceita, embora use a solução ingênua.
 */
#include <stdio.h>

int f91( int n ) {
    if( n < 101 )
        return f91( f91(n + 11) );

    return n - 10;
}

int main() {
    int n;
    while( scanf("%d", &n) && n != 0 )
        printf( "f91(%i) = %i\n", n, f91(n) );
    return 0;
}

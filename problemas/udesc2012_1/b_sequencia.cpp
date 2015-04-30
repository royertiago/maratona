#include <stdio.h>

int main() {
    int a, n, y;
    while( scanf( "%d %d %d", &a, &n, &y ) != EOF && n != 0 ) {
        int x = (y - a)/n;
        if( n * x + a == y )
            printf( "%d\n", x + 1 );
        else
            printf( "X\n" );
    }
    return 0;
}

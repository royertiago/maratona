#include <stdio.h>

int main() {
    int n, sum, x, c = 1;
    while( scanf( "%d", &n ) != EOF && n != 0 ) {
        sum = 0;
        for( int i = 0; i < n; i++ ) {
            scanf( "%d", &x );
            sum += x;
        }
        printf( "Teste %i\n%i\n\n", c++, sum );
    }
    return 0;
}

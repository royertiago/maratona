#include <stdio.h>

int main() {
    int c = 1;
    int n;
    while( scanf( "%d", &n ) != EOF && n != -1 ) {
        long long i = (1ll << (n+1)) - (1ll << n) + 1;
        printf( "Teste %i\n%lld\n\n", c++, i*i );
    }
    return 0;
}

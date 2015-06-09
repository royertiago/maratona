#include <stdio.h>

int cache[(int) 1e6+1];
int largest_cached = 1;

int solve( int input ) {
    if( largest_cached >= input )
        return cache[input] % 10;

    long long d = cache[largest_cached];
    for( int i = largest_cached + 1; i <= input; i++ ) {
        long long  j = i;
        while( j % 10 == 0 )
            j /= 10;

        while( j % 5 == 0 ) {
            d /= 2;
            j /= 5;
        }

        cache[i] = d = (d * j) % (long long) 1e9;
    }
    largest_cached = input;
    return d % 10;
}

int main() {
    cache[0] = cache[1] = 1;
    int n, i = 1;
    while( scanf( "%d", &n ) != EOF ) {
        printf( "Instancia %d\n%d\n\n", i++, solve(n) );
    }
    return 0;
}

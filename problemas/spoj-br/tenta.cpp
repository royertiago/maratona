#include <stdio.h>
#include <algorithm>

int a[8];
int n;

bool next() {
    if( n == 1 )
        return false;

    int j = n - 2;
    for( ; j >= 0; j-- )
        if( a[j] < a[j + 1] )
            break;

    if( j == -1 )
        return false;

    // Everyone from j to n must be swapped.
    int i = j + 1;
    for( ; i < n; i++ )
        if( a[i] <= a[j] )
            break;
    i--;

    // i contains the first element smaller than j.
    std::swap( a[i], a[j] );
    std::reverse( a + j + 1, a+n );
    return true;
}

int main() {
    const char * delim = "";
    while( scanf( "%d", &n ) != EOF, n != 0 ) {
        for( int i = 0; i < n; i++ )
            scanf( "%d", &a[i] );

        printf( delim );
        delim = "\n";

        std::sort( a, a+n );
        do {
            const char * delim = "";
            for( int i = 0; i < n; i++ ) {
                printf( "%s%d", delim, a[i] );
                delim = " ";
            }
            printf( "\n" );
        } while( next() );
    }

    return 0;
}

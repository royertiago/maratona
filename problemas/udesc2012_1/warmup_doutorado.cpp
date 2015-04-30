#include <stdio.h>

char dummy[128];

int main() {
    int N;
    scanf( "%d", &N );
    while( N-- ) {
        int a, b;
        if( scanf( "%d + %d", &a, &b ) == 2 )
            printf( "%d\n", a + b );
        else {
            printf( "skipped\n" );
            fgets( dummy, 128, stdin );
        }
    }
    return 0;
}

#include <stdio.h>

int main() {
    int a, b;
    while( scanf( "%d %d", &a, &b ) != EOF && (a != 0 || b != 0) ) {
        if( a < 0 || a > 5 || b < 0 || b > 5 )
            printf( "Og diz: Eh um NP!\n" );
        else
            printf( "%d\n", a + b );
    }
}

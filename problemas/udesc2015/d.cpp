#include <stdio.h>

void print( int i ) {
    if( i < 1000 )
        printf( "%d", i );
    else {
        print( i/1000 );
        printf( ".%03d", i % 1000 );
    }
}

int scan() {
    int a = 0, b = 0, c = 0;
    int r = scanf( "%d.%d.%d", &a, &b, &c );
    while( r++ < 3 ) {
        c = b;
        b = a;
        a = 0;
    }
    return a * 1000 * 1000 + b * 1000 + c;
}

int main() {
    int C;
    char dummy[51];
    while( scanf( "%d", &C ) != EOF && C != 0 ) {
        int favor = 0, contra = 0;
        for( int i = 0; i < C; i++ ) {
            scanf( "%s", dummy ); // ignorar o nome da cidade
            favor += scan();
            contra += scan();
        }
        print( favor + contra );
        printf( " " );
        print( favor );
        printf( " " );
        print( contra );
        printf( "\n" );
    }
    return 0;
}

/* 1252.cpp
 * Problema: https://www.urionlinejudge.com.br/judge/en/problems/view/1252
 */

#include <stdio.h>
#include <algorithm>

using std::sort;

int values[10000];

int main() {
    int m, n;
    while( scanf("%i %i\n", &m, &n) == 2 && m != 0 ) {
        printf( "%i %i\n", m, n );
        int i;
        for( i = 0; i < m; ++i )
            scanf( "%i", &values[i] );
        sort( values, values + i, [&n]( int a, int b ){
                if( a % n < b % n ) return true;
                if( a % n > b % n ) return false;
                if( a % 2 != 0 )
                    if( b % 2 == 0 ) return true;
                    else return a > b;
                if( b % 2 != 0 ) return false;
                return a < b;
            } );
        for( int i = 0; i < m; ++i ) printf( "%i\n", values[i] );
    }
    printf( "0 0\n" );
    return 0;
}

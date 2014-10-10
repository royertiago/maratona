/* 424.cpp
 * Problema: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=365
 */
#include <stdio.h>
#include <string.h>

#define MOD 10000000 // 10**7
#define LOG 7
#define SLOG "7"
#define SIZE 15

int numbers[100][SIZE];

int min( int i, int j ) { return i < j ? i : j; }
int max( int i, int j ) { return i > j ? i : j; }

void parse_num( int i, char * num ) {
    int len = strlen( num ), j = SIZE-1;
    while( len > 0 ) {
        sscanf( num + max(0, len -= LOG), "%d", &numbers[i][j--] );
        num[len] = '\0';
    }
    while( j >= 0 )
        numbers[i][j--] = 0;
}

int main() {
    char num[101];
    int i = 0;
    while( scanf( "%s", num ) != EOF && strcmp(num, "0") != 0 ) {
        parse_num( i++, num );
    }

    for( int k = 0; k < SIZE; k++ )
    for( int j = 1; j < i; ++j )
        numbers[0][k] += numbers[j][k];

    for( int t = SIZE-1; t > 0; t-- ) {
        numbers[0][t-1] += numbers[0][t] / MOD;
        numbers[0][t] %= MOD;
    }
    bool print = false;
    for( int t = 0; t < SIZE; t++ ) {
        if( numbers[0][t] != 0 ) {
            if( !print ) {
                print = true;
                printf( "%d", numbers[0][t] );
                continue;
            }
            print = true;
        }
        if( print )
            printf( "%0" SLOG "d", numbers[0][t] );
    }
    if( !print ) printf( "0\n" );
    else printf( "\n" );
    return 0;
}

/* 2190.cpp
 * Problema B da rodada 1C do Google Code Jam de 2008.
 *
 * Mirror: http://acm.cs.ecnu.edu.cn/problem.php?problemid=2190
 */
#include <stdio.h>

typedef long long unsigned ll;
char input[41];
/* pd[i][j] é a quantidade de formas que podemos manipular os
 * elementos input[0..i] de forma que o resto da divisão por 210 seja j. */
ll pd[40][210];

// rem(i) retorna input[i..j] % 210
ll rem( unsigned i, unsigned j ) {
    unsigned mod = 0;
    for( unsigned k = i; k <= j; k++ )
        mod = (mod * 10 + (input[k]-'0')) % 210;
    return mod;
}

ll solve() {
    for( int i = 0; i < 210; ++i ) 
        for( int j = 0; j < 40; ++j )
            pd[j][i] = 0;

    int p = 0;
    for( ; input[p]; ++p ) {
        pd[p][rem(0,p)]++;
        for( int j = 0; j < p; ++j ) {
            ll mod = rem(j+1, p);
            for( unsigned k = 210; k < 2*210; k++ ) {
                pd[p][(k + mod) % 210] += pd[j][k-210];
                pd[p][(k - mod) % 210] += pd[j][k-210];
            }
        }
    }
    
    ll result = 0;
    for( unsigned k = 0; k < 210; k++ )
        if( k % 2 == 0 || k % 3 == 0 || k % 5 == 0 || k % 7 == 0 )
            result += pd[p-1][k];

    return result;
}

int main() {
    int N;
    scanf( "%d", &N );
    for( int i = 1; i <= N; ++i ) {
        scanf( "%s", input );
        printf( "Case #%d: %llu\n", i, solve() );
    }
    return 0;
}

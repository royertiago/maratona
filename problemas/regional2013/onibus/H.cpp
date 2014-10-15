/* H.cpp
 * Problema da etapa regional da Maratona de 2013
 *
 * Versão alternativa: https://www.urionlinejudge.com.br/judge/problems/view/1474
 */
#include <stdio.h>


typedef long long int matriz[2][2];
#define MOD (1000*1000)

void mult( matriz a, matriz b ) {
    matriz aux;
    for( int i = 0; i < 2; ++i )
        for( int j = 0; j < 2; ++j ) {
            aux[i][j] = 0;
            for( int k = 0; k < 2; ++k )
                aux[i][j] += a[i][k]*b[k][j];
        }
    for( int i = 0; i < 2; ++i )
        for( int j = 0; j < 2; ++j )
            a[i][j] = aux[i][j] % MOD;
}

long long int N, K, L;

int solve() {
    matriz x = {1, 0, 0, 1};
    matriz a = {K % MOD, L % MOD, 1, 0};
    while( N != 0 ) {
        if( N % 2 != 0 )
            mult( x, a );
        mult( a, a );
        N >>= 1;
    }
    return x[0][0];
}

int main() {
    scanf( "%lld%lld%lld", &N, &K, &L );
    N /= 5;
    printf( "%06d\n", solve() );
}

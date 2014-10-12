/* 1747.cpp
 * Problema: http://acm.timus.ru/problem.aspx?space=1&num=1747
 */
#include <stdio.h>

/* Continuando de 1747.a.cpp, podemos subtrair as duas fórmulas de recorrência
 * para Fm e Gm para obter
 *      Fm - Gm = (n+1)( 2n - 2n-1 ) Fn
 *              = -(n+1) Fn
 * Ou seja, Gm = Fm + (n+1) Fn.
 * Substituindo na fórmula para Fm, obtemos
 *      F(n+1) = (n+1)( (2n+1) F(n) + n F(n-1) )
 */

typedef long long ll;

int main() {
    ll F0 = 1, F1 = 0, F2;
    ll N, P;
    scanf( "%llu%llu", &N, &P );
    N--;

    for( ll n = 1; n < N; ++n ) {
        F2 = (n+1) *(  ( (2*n+1)*F1 + n*F0 ) % P ) % P;
        F0 = F1;
        F1 = F2;
    }
    printf( "%llu\n", F2 );
}

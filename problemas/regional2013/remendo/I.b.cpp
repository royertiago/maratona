/* I.b.cpp
 * Problema da etapa regional da Maratona de 2013.
 *
 * Este arquivo otimiza a busca binária feita no arquivo I.a.cpp,
 * deslocando ponteiros pelo vetor ao invés de refazer a busca toda vez.
 */
#include <stdio.h>

int pd[1000], furo[1000], N, C, T1, T2;

int shift;
int f( int i ) {
    return (furo[ (i + shift) % N ] - furo[shift] + C) % C;
}

int min( int i, int j ) { return i < j ? i : j; }
int max( int i, int j ) { return i > j ? i : j; }

int solve() {
    int tmp = min(T1, T2);
    T2 = max(T1, T2);
    T1 = tmp;

    int i;
    for( i = 0; f(i) <= T1 && i < N; ++i )
        pd[i] = T1;
    int j;
    for( j = 0; f(i) <= T2 && i < N; ++i ) {
        while( f(j+1) < f(i) - T1 ) j++;
        pd[i] = min( T2, pd[j] + T1 );
    }
    int k;
    for( k = 0; i < N; ++i ) {
        while( f(j+1) < f(i) - T1 ) j++;
        while( f(k+1) < f(i) - T2 ) k++;
        pd[i] = min( pd[j] + T1, pd[k] + T2 );
    }
    return pd[N-1];
}

int main() {
    scanf( "%d%d%d%d", &N, &C, &T1, &T2 );
    for( int i = 0; i < N; ++i )
        scanf( "%d", &furo[i] );
    
    int best = 1000*1000;
    for( shift = 0; shift < N; ++shift )
        best = min( best, solve() );

    printf( "%d\n", best );
    return 0;
}

/* I.a.cpp
 * Problema da etapa regional da Maratona de 2013.
 */
#include <stdio.h>

#define HUGE 10000000

int furo[1000];
int N, C, T1, T2;
int pd[1000];

int min( int i, int j ) { return i < j ? i : j; }
int max( int i, int j ) { return i > j ? i : j; }

int shift;
int f( int i ) {
    return (furo[ (i + shift) % N ] - furo[shift] + C) % C;
}
/* shift representa a seguinte operação: gire o pneu até que o furo do índice
 * shift fique no topo. Risque aquele furo, e meça os demais relativamente a
 * este furo, inclusive aqueles que estavam antes do furo.
 *
 * Fixado um shift, pd[i] é a forma mais econômica de cobrir os furos
 * de índice 0, 1, ..., i. Note que desconsideramos a possibilidade de cobrir
 * os furos que vieram, na roda, antes do furo shift; temos, portanto,
 * que testar todos os shifts possíveis. Eventualmente algum desses shifts
 * ficará na "fronteira" de alguma solução ótima, e então acertamos o chute.*/

// Retorna o maior índice x tal que f(x) < i
int rindex( int i ) {
    int min = 0, max = N-1;
    while( min < max ) {
        int middle = min + (max - min + 1)/2;
        if( f(middle) < i )
            min = middle;
        else
            max = middle - 1;
    }
    return min;
}

int solve() {
    int first = rindex(min(T1, T2)), second = rindex(max(T1, T2));
    int first_limit = f(first+1) == min(T1, T2) ? first+1 : first;
    int second_limit = f(second+1) == max(T1, T2) ? second+1 : second;
    for( int i = 0; i <= first_limit; ++i )
        pd[i] = min(T1, T2); // em first_limit ainda cobrimos o primeiro furo
    for( int i = first_limit + 1; i <= second_limit; ++i )
        /* Aqui devemos testar: é melhor por uma tira de tamanho max(T1, T2)
         * ou por várias de tamanho min(T1,T2)? */
        pd[i] = min( max(T1, T2), pd[rindex(f(i)-min(T1,T2))] + min(T1, T2) );
    for( int i = second_limit + 1; i < N; ++i )
        /* Para testar o efeito de por uma tira de tamanho T1, procuramos
         * o primeiro furo não coberto por esta tira - ele estará antes
         * de f(i)-T1, pois os furos que estão no intervalo [f(i)-T1, f(i)]
         * nós conseguimos cobrir. pd[rindex(d)] retorna o custo de cobrir
         * todos os furos que ficam no intervalo [0, d); basta somar o custo
         * de cobrir o furo com uma tira T1. */
        pd[i] = min( pd[rindex(f(i)-T1)] + T1, pd[rindex(f(i)-T2)] + T2 );
    return pd[N-1];
}

int main() {
    scanf( "%d%d%d%d", &N, &C, &T1, &T2 );
    for( int i = 0; i < N; ++i )
        scanf( "%d", &furo[i] );

    int best = HUGE;
    for( shift = 0; shift < N; ++shift )
        /* Nenhum dos casos de teste originais de fato exige que algum remendo
         * tenha de ser feito atravessando o início do vetor; o caso de teste
         * I_0 foi adicionado apenas para registrar esta possibilidade. */
        best = min( best, solve() );
    printf( "%d\n", best );
    return 0;
}

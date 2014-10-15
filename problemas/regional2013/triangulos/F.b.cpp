/* F.b.cpp
 * Problema da etapa regional da Maratona de 2013.
 *
 * Este arquivo resolve o problema avançando com 
 * três ponteiros a lista de pontos.
 */
#include <stdio.h>

int N, t[100*1000];

int binary_search( int value ) {
    int min = 0, max = N-1;
    while( min < max ) {
        int middle = min + (max - min)/2;
        if( value <= t[middle] )
            max = middle;
        else
            min = middle + 1;
    }
    return max;
}

int solve() {
    if( t[N-1] % 3 != 0 ) return 0;
    int offset = t[N-1] / 3;
    int i = 0, j = binary_search(offset), k = binary_search(offset*2);
    int total = 0;
    while( k < N ) {
        if( t[i] + offset == t[j] && t[j] + offset == t[k] ) {
            // Se os três ponteiros formam um triângulo, incremente tudo.
            total++;
            i++;
            j++;
            k++;
        }
        /* Senão, ao menos algum destes pontos está "atrás"; isto é, eles
         * não formam um triângulo pois algum dos vértices é pequeno demais.
         * Este vértice é incrementado.
         *
         * Note que as comparações são por menor ou igual; ao menos uma
         * das comparações será estritamente menor, pois o caso em que
         * os três são iguais já foi eliminado no teste anterior.
         * E não podemos fortalecer a comparação para menor que ou
         * maior que pois pode ser que dois ponteiros sejam iguais,
         * mas menores que o terceiro. */
        else if( t[i] + offset <= t[j] && t[i] + 2*offset <= t[k] )
            // Caso t[i] esteja antes de algum dos dois
            ++i;
        else if( t[i] + offset >= t[j] && t[j] + offset <= t[k] )
            // Caso t[i] tenha passado t[j], mas t[j] esteja antes de t[k]
            ++j;
        else if( t[k] <= t[i] + 2*offset && t[k] <= t[j] + offset )
            // Último caso: t[k] está atrás dos outros dois.
            ++k;
    }
    return total;
}

int main() {
    scanf( "%d%d", &N, &t[0] );
    for( int i = 1; i < N; ++i ) {
        scanf( "%d", &t[i] );
        t[i] += t[i-1];
    }
    printf( "%d\n", solve() );
    return 0;
}

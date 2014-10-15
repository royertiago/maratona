/* F.a.cpp
 * Problema da etapa regional da Maratona de 2013.
 *
 * Este arquivo contém uma solução baseada em busca binária.
 *
 * Versão alternativa: https://www.urionlinejudge.com.br/judge/problems/view/1472
 */
#include <stdio.h>

int N, t[100*1000];

// Retorna o índice do menor valor maior ou igual a value.
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
    /* offset é o tamanho do arco descrito por um lado do triângulo.
     * Para cada ponto distante entre 1 e offset do início da circunferência,
     * deve haver exatamente um ponto a um offset de distância e a dois offsets
     * de distância. binary_search retorna um índice; buscamos se o valor
     * correspondente forma um triângulo com o ponto analisado agora. */
    int total = 0;
    for( int i = 0; t[i] <= offset; ++i )
        if( t[binary_search(t[i] + offset)] == t[i] + offset
         && t[binary_search(t[i] + 2*offset)] == t[i] + 2*offset )
            total++;
    return total;
}

int main() {
    scanf( "%d%d", &N, &t[0] );
    for( int i = 1; i < N; ++i ) {
        scanf( "%d", &t[i] );
        t[i] += t[i-1];
        /* t[i] contém a distância radial do ponto i 
         * até o início da circunferência. */
    }
    printf( "%d\n", solve() );
    return 0;
}

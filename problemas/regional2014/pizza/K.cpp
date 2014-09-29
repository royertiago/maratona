/* K.cpp
 * Problema da etapa regional da maratona de 2014
 */
#include <stdio.h>

int min( int i, int j ) { return i < j ? i : j; }
int max( int i, int j ) { return i > j ? i : j; }

int main() {
    const char * ans = "NS"; // ans[false] == 'N', ans[true] == 'S'
    int C, N, K, a;
    scanf( "%d %d", &C, &N );
    K = C / N;

    /* Faremos o corte na posição t, de forma que a primeira azeitona
     * fique no pedaço [t, t+K), a segunda no pedaço [t+K, t + 2K) etc.
     * Isto é: se an é a n-ésima azeitona, 
     *      t + nK <= an < t + (n+1) K
     * ou
     *      nK - an <= t < (n+1) K - an
     * Isto impõe uma série de restrições ao ponto de corte.
     * Como t precisa satisfazer todas elas, basta armazenar a mais
     * restritiva de cada lado, e ver se a diferença entre
     * elas é positiva (isto é, exite algum t viável ali dentro). */
    int lower_bound = -1000000; // "== INT_MIN"
    int upper_bound = 1000000;
    for( int i = 0; i < N; ++i ) {
        scanf( "%d", &a );
        lower_bound = max(i*K - a,     lower_bound);
        upper_bound = min((i+1)*K - a, upper_bound);
    }
    printf( "%c\n", ans[ upper_bound - lower_bound > 0 ] );
    return 0;
}

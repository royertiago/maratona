#include <stdio.h>
#include <algorithm>

#define HUGE 1e8

int pos[(int)1e6 + 1];
int N;
/* pd[i][j] é a menor quantidade de movimentos necessário
 * para que alguma das rãs chege ao destino,
 * assumindo que a rã mais à esquerda está na posição i
 * e a rã mais à direita está na posição i + j.
 */
int pd[(int)1e6 + 1][10];

int solve() {
    /* As rãs não podem pular mais do que 10 unidades;
     * nossa condição de busca (quais valores de i e j podem ser usados
     * para minimizar o estado atual) será baseada nesta restrição,
     * então definir pos[N] serve como "sentinela".
     */
    pos[N] = pos[N-1] + 20;

    int M = N - 1;
    /* M é a posição máxima alcançável por uma rã;
     * é a posição em que uma das rãs deve terminar o jogo.
     */
    for( int k = 1; k < 10; k++ )
        if( N-k > 0 ) {
            /* pd[M-k][k] é a situação com uma das rãs
             * na posição M-k e a outra k posições à frente,
             * na posição M-k+k == M.
             *
             * O if existe apenas para evitar erros de segmentação.
             */
            pd[M-k][k] = 0;
        }

    for( int i = M - 1; i >= 0; i-- )
        for( int j = 1; j < 10 && i + j < M; j++ ) {
            int min_moves = HUGE;
            /* Passaremos por todas as possíveis próximas posições
             * para a rã atual.
             * Começamos de i + j + 1 pois temos de pular sobre a outra rã.
             *
             * A condição usada, pos[next_pos] <= pos[i] + 10,
             * funciona por causa do sentinela.
             */
            for( int next_pos = i + j + 1; pos[next_pos] <= pos[i] + 10; next_pos++ ) {
                int other_pos = i + j;
                int delta = next_pos - other_pos;
                min_moves = std::min( min_moves, pd[other_pos][delta] + 1 );
            }
            pd[i][j] = min_moves;
            /* Observe que, caso não hajam movimentos válidos,
             * min_moves == HUGE; graças ao std::min acima,
             * estes valores se propagam até o início da tabela.
             */
        }

    if( pd[0][1] == HUGE )
        return -1;

    return pd[0][1];
}

int main() {
    while( scanf( "%d", &N ) != 0 && N != 0 ) {
        for( int i = 0; i < N; i++ )
            scanf( "%d", &pos[i] );
        printf( "%d\n", solve() );
    }
}

/* Problema C da seletiva doméstica da UDESC de 2015.
 *
 * Programação dinâmica. Complexidade: n^3.
 */
#include <stdio.h>
#include <algorithm>

/* cards1[0], cards2[0] cards3[0] sempre assumirão o valor zero. */
int card_count;
int cards1[101];
int cards2[101];
int cards3[101];

/* dp[i][j][k] é a maior quantidade de pontos que pode ser obtida
 * quando as pilhas de cartas tiverem tamanho i, j e k,
 * respectivamente.
 *
 * Não estamos indexando em zero para facilitar a verificação:
 * nunca fará sentido usar a carta zero, pois, por convenção,
 * ela será sempre zero.
 *
 * Estamos, de certa forma, indexando em -1.
 * É como se colocássemos, artificialmente, uma carta 0
 * embaixo de cada monte.
 * (Observe que precisaremos ajustar card_count também.)
 *
 * Caso i, j ou k forem zero, assumiremos que dp[i][j][k] é zero.
 * Ou seja, estamos usando dois níveis de sentinela:
 * um nas cartas, e outro na própria programação dinâmica.
 *
 * Sem nossas convenções, card_count pode assumir os valores 1, 2, ..., 100;
 * e os índices das cartas seríam 0, 1, ..., 99.
 * Agora, card_count vai até 101, e os índices das cartas até 100.
 * Portanto, se quisermos retornar o valor dp[card_count][card_count][card_count]
 * como resposta da programação dinâmica,
 * precisamos permitir que i, j e k vão até 101.
 * Portanto, precisamos de 102 prosições na tabela.
 */
int dp[102][102][102];

/* Retorna a solução do problema para i, j, k,
 * assumindo que i, j, k > 0; e que
 * todas as instâncias (i_0, j_0, k_0) com i_0 <= i, j_0 <= j, k_0 <= k
 * e ao menos uma das desigualdades estritas estão populados no vetor pd.
 */
int solve( int i, int j, int k ) {
    int max = 0;
    int ci = cards1[i-1];
    int cj = cards2[j-1];
    int ck = cards3[k-1];
    /* Existem i cartas na pilha, cards1[i-1] é a carta do topo.
     */

    if( ci + cj + ck < 15 && (ci + cj + ck) % 2 == 1 )
        max = std::max( max, ci*cj*ck + dp[i-1][j-1][k-1] );
    if( ci + cj < 15 && (ci + cj) % 2 == 1 )
        max = std::max( max, ci*cj + dp[i-1][j-1][k] );
    if( ci + ck < 15 && (ci + ck) % 2 == 1 )
        max = std::max( max, ci*ck + dp[i-1][j][k-1] );
    if( cj + ck < 15 && (cj + ck) % 2 == 1 )
        max = std::max( max, cj*ck + dp[i][j-1][k-1] );
    if( ci < 15 && ci % 2 == 1 )
        max = std::max( max, ci + dp[i-1][j][k] );
    if( cj < 15 && cj % 2 == 1 )
        max = std::max( max, cj + dp[i][j-1][k] );
    if( ck < 15 && ck % 2 == 1 )
        max = std::max( max, ck + dp[i][j][k-1] );

    return max;
}

int solve() {
    for( int i = 0; i <= card_count; i++ )
        for( int j = 0; j <= card_count; j++ )
            dp[i][j][0] = dp[i][0][j] = dp[0][i][j] = 0;

    /* Já iteramos sobre todas as triplas (i, j, k)
     * que possuem ao menos um zero.
     *
     * Agora, iteraremos sobre todas as triplas (i, j, k)
     * em que nenhum valor é zero.
     * Iteraremos primeiro sobre todas as triplas para as quais
     * i + j + k = 3; depois, para todas as quais i + j + k = 4,
     * e assim por diante.
     */
    for( int total_sum = 3; total_sum <= 3 * card_count; ++total_sum ) {
        /* Primeiro, iteraremos sobre todas as triplas (i, j, k)
         * tais que i+j = 2; depois, i+j = 3, e assim por diante.
         * Precisamos tomar cuidado com dois valores-limite.
         * Não faz sentido que a soma seja maiaor que 2 * card_count,
         * nem que k tenha que ser maior que card_count para que
         * a soma i + j + k feche total_sum.
         */
        for( int first_sum = std::max(2, total_sum - card_count);
             first_sum < total_sum && first_sum <= 2 * card_count;
             ++first_sum
           )
        {
            /* Agora, iteraremos sobre todos os i's.
             * Também precisamos tomar cuidado para que os valores de j
             * façam sentido.
             */
            for( int i = std::max(1, first_sum - card_count);
                i < first_sum && i <= card_count;
                ++i )
            {
                int j = first_sum - i;
                int k = total_sum - first_sum;
                dp[i][j][k] = solve(i, j, k);
            }
        }
    }
    return dp[card_count][card_count][card_count];
}

int main() {
    while( scanf("%d", &card_count) == 1 && card_count != 0 ) {
        cards1[0] = cards2[0] = cards3[0] = 0;
        for( int i = card_count; i >= 1; i-- )
            scanf( "%d %d %d", &cards1[i], &cards2[i], &cards3[i] );
        ++card_count;

        printf( "%d\n", solve() );
    }
    return 0;
}

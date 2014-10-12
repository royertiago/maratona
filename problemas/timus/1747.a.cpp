/* 1747.cpp
 * Problema: http://acm.timus.ru/problem.aspx?space=1&num=1747
 */
#include <stdio.h>

/* Simples relação de recorrência.
 * Exclua a cidade inicial/final - ela é fixa, então não influencia nas contas.
 * Defina
 *  Fn = quantidade de passeios válidos, com n cidades
 *  Gn = quantidade de passeios com exatamente uma repetição
 * 
 * Por exemplo, para n = 2, temos os seguintes passeios:
 *  1122
 *  1212
 *  1221
 *  2112
 *  2121
 *  2211
 * Os passeios 2 e 5 são válidos, portanto F_2 == 2. Já os demais quatro são
 * inválidos, mas apenas o 3 e o 4 possuem exatamente uma repetição, portanto
 * G_2 == 2.
 *
 * Por conveniência, defina m = n+1; Construiremos Fm e Gm a partir de Fn e Gn.
 *
 * Para Fm: fixe uma cidade inicial. Para construir um caminho F começando
 * nesta cidade, podemos emendar outro caminho F, e inserir a cidade inicial
 * em algum ponto no meio. Existem 2n pontos disponíveis para inserção; como
 * também podemos adicionar um caminho G e pôr a cidade no meio da repetição,
 * temos exatamente 2n*Fn + Gn jeitos de formar um caminho com aquela cidade
 * inicial. Existem n+1 escolhas de cidade inicial, portanto temos
 *      Fm = (n+1) * ( 2*n * Fn + Gn ).
 * Observe que estes dois jeitos são disjuntos: no primeiro caso, a inserção
 * precisa ser feita entre duas cidades distintas, e o exato oposto ocorre no
 * segundo caso. Também observe que as duas situações cobrem todos os caminhos;
 * para ver isso, pegue um caminho válido qualquer, e remova a cidade inicial
 * e sua outra aparição no meio. Se o caminho resultante é válido, o caminho
 * original seria formado pela primeira regra; caso não seja, necessariamente
 * haverá exatamente uma repetência - sendo formado pela segunda regra.
 *
 * Para Gm: fixe uma cidade que irá se repetir. Podemos pegar um caminho G e
 * inserir a repetição no meio da repetição anterior, mantento exatamente
 * uma repetição no caminho. Ou, a partir de um caminho F, inserir a repetição
 * em algum dos 2n+1 espaços disponíveis. Temos, portanto, (2n+1)*Fn + Gn
 * novos caminhos para cada cidade fixada, resultando em
 *      Gm = (n+1) * ( (2n+1)*Fn + Gn ).
 * Um raciocínio similar ao anterior mostra completude e exclusão mútua.
 *
 * Por último, note que F0 = 1, pois existe um único caminho válido, o caminho
 * vazio; e que G0 = 0 pois não é possível formar caminhos em que uma cidade 
 * se repete sem cidades.
 */

typedef long long unsigned ll;

int main() {
    ll N, P;
    scanf( "%llu%llu", &N, &P );
    N--;
    ll Fn = 1, Fm;
    ll Gn = 0, Gm;

    for( ll n = 0; n < N; ++n ) {
        Fm = (n+1) * ((  2*n * Fn + Gn) % P) % P;
        Gm = (n+1) * (((2*n+1)*Fn + Gn) % P) % P;
        Fn = Fm;
        Gn = Gm;
    }
    printf( "%llu\n", Fn );
    return 0;
}

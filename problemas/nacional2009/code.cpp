/* code.cpp
 * Problema C da etapa nacional da Maratona de 2009.
 *
 * Manipulações algébricas e da entrada para chegar num programa linear
 * e mais manipulações para resolver este programa com um algoritmo guloso.
 *
 *
 * Defina d[i] como sendo o vetor de diferenças da entrada. Cada operação
 * num intervalo da entrada pode ser resumido em uma operação em dois
 * (ou um) elemento do vetor de diferenças: rotacionar para cima os
 * elementos de input[i..j] equivale a adicionar 1 em d[i] e remover 1
 * de d[j+1] (ou não remover, caso j seja o último elemento do vetor).
 *
 * Note que d[i] pertence a Z_26, os inteiros módulo 26.
 *
 * Reduzimos o problema a executar operações de três tipos no vetor de
 * diferenças: incrementar uma posição i e decrementar uma posição j,
 * ou apenas incrementar i ou apenas incrementar j. Queremos levar o vetor
 * de diferenças para 0 com o menor número destas operações. Note que,
 * por exemplo, não faz sentido que hajam operações de ambos os últimos
 * dois tipos, pois cada par de operações destas poderia ser convertida
 * numa operação binária (o primeiro tipo).
 *
 * Imporemos duas restrições na solução achada: nenhum dos d[i]s "dará
 * uma volta" ou mesmo irá passar pelo mesmo elemento duas vezes.
 * Isto é: cada d[i] será apenas incrementado ou decrementado no percurso.
 * Podemos assumir que existe uma solução ótima neste formato: caso
 * houvesse alguma solução ótima em que algum elemento vai e volta,
 * podemos remover todas as operações unárias envolvidas neste deslocamento
 * e trocar as binárias para serem unárias que não afetem o elemento em
 * questão. Isto é, podemos nos preocupar em apenas achar soluções em que
 * cada elemento é incrementado ou decrementado.
 *
 * Podemos adotar a seguinte estratégia: escolheremos algum subconjunto
 * dos d[i] para serem decrementados. Somando seus valores, sabemos quantas
 * operações de decremento temos de fazer. Para cada i que não está neste
 * subconjunto, o custo de girá-lo para cima é 26 - d[i]. Somando-se estes
 * valores, teremos a quantidade de incrementos que devemos fazer.
 * Chame estas duas quantidades de sub e add, respectivamente. min(sub, add)
 * operações podem ser feitas com operações binárias, enquanto que as demais
 * max(sub, add) - min(sub, add) precisam ser unárias. No final, precisamos
 * de, exatamente, max(sub, add) operações para resolver o problema.
 * Queremos minimizar este valor.
 *
 * Transformemos isto num programa linear. Defina o vetor 'a' por
 * a[i] = quantidade de elementos em d de valor i. a terá tamanho 26.
 * Usaremos 26 variáveis x_i; a semântica que daremos é: x_i é a quantidade
 * de elementos do vetor d que possuem valor i que escolheremos decrementar
 * até zero. Isso nos dá 52 restrições lineares: 0 <= x_i <= a[i].
 * O custo de decrementar os valores escolhidos é \sum_{i=0}^{25} i * x_i,
 * e o custo de incrementar os restantes é \sum_{i=0}^{25} (26-i)*(a[i]-x_i).
 * Queremos minimizar o máximo entre os dois valores.
 *
 * Entretanto, programas lineares minimizam funções lineares, não máximos;
 * para termos qualquer esperança de resolver isto usando algo tipo simplex,
 * precisamos modificar a função de custo. Dividiremos o programa linear
 * em dois: no primeiro, assumiremos que o máximo se dá pela primeira
 * expressão, e queremos minimizar justamente esta expressão; e fazemos
 * o contrário no segundo programa linear. Para que nossa suposição seja
 * verdadeira, iremos adicionar, ao primeiro programa linear, a restrição
 * de que o primeiro somatório é maior que o segundo, e a restrição oposta
 * ao segundo programa linear. Portanto, possuimos os seguintes programas:
 *
 * 1) minimizar sum i * x_i
 *    sujeito a  0 <= x_i <= a[i]
 *              sum i * x_i >= sum (26 - i) * (a[i] - x_i)
 *
 * 2) minimizar sum (26-i) * (a[i] - x_i)
 *    sujeito a  0 <= x_i <= a[i]
 *              sum i * x_i <= sum (26 - i) * (a[i] - x_i)
 *
 * Note que as últimas restrições de cada programa são lineares.
 * Agora, passamos todos os x_i para o lado esquerdo da última desigualdade
 * do primeiro programa linear. Obtemos
 *  sum i * x_i - sum (26 - i) * (- x_i) >= sum (26 - i) * a[i]
 *                 sum x_i( i + (26-i) ) >= sum (26 - i) * a[i]
 *                            26 sum x_i >= sum (26 - i) * a[i]
 *                               sum x_i >= ceil( (sum (26 - i)*a[i]) / 26)
 * Ou seja: para esta restrição linear, o "peso" de cada x_i é o mesmo.
 * Como queremos minimizar sum i * x_i, basta escolher x_i = a[i]
 * para i = 0, 1, 2, ... até satisfazer o limite desta restrição linear.
 * Portanto, um algoritmo guloso resolve este programa linear.
 *
 * A mesma manipulação transforma o segundo programa linear em
 *      26 sum x_i <= sum (26 - i) * a[i]
 *         sum x_i <= floor( (sum (26 - i) * a[i]) / 26)
 * com o objetivo de minimizar a soma
 *      sum (26 - i)*a[i] - sum x_i * (26-i)
 * Como 26-i é maior com i próximo de zero, escolhemos x_i = a[i]
 * para i = 0, 1, 2, ... enquanto não estouramos a restrição linear.
 *
 * Agora, basta computar os respectivos somatórios e extrair o mínimo.
 *
 * (Note que aqui extraimos o mínimo, pois em cada programa linear
 *  impomos que um dos somatórios seria o máximo e que é este somatório
 *  que corresponde à resposta. Caso os resultados sejam diferentes,
 *  sabemos que em um dos programas lineares não atingimos o ótimo; isto
 *  é, nossa hipótese estava errada - a resposta está no outro somatório.
 *  Portanto, retornamos o outro.)
 */
#include <stdio.h>
#include <algorithm>

#define MAX 1000

char input[MAX+1];
int a[26];

int solve() {
    for( int & c : a ) c = 0;
    a[input[0]-'a']++;
    for( int i = 1; input[i]; i++ )
        a[ (input[i]-input[i-1]+26) % 26 ]++;

    int sum = 0;
    for( int i = 0; i < 26; ++i )
        sum += a[i]*(26-i);

    int upper = (sum + 25)/26;
    int upper_total = 0;
    int upper_count = 0;

    int lower = sum/26;
    int lower_total = sum;
    int lower_count = 0;

    /* Chamei o primeiro programa linear de upper, o somatório
     * dos x_i de upper_count, e a função de custo deste somatório
     * de upper_total. O segundo programa foi chamado de lower. */
    for( int i = 0; i < 26; ++i ) {
        int add = std::min(a[i], upper - upper_count);
        int sub = std::min(a[i], lower - lower_count);
        upper_count += add;
        upper_total += i * add;
        lower_count += sub;
        lower_total -= (26 - i) * sub;
    }
    return std::min( upper_total, lower_total );

}

int main () {
    while( scanf("%s", input) != EOF && input[0] != '*' ) {
        printf( "%d\n", solve() );
    }
    return 0;
}

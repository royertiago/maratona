/* Defina a estrutura fib{ int a, b }.
 * fib irá armazenar as etapas parcias do cálculo de Fibonacci.
 * Defina base = {0, 1}, e next({a, b}) = {(a + b) % 1000, a}.
 *
 * Ao aplicar next repetidas vezes à base,
 * obtemos os valores da sequência de Fibonacci, mas apenas os três últimos valores.
 * Isto é, next^n( base ) = {F_n, F_{n-1}}.
 * (Esta fórmula precisa da interpretação adicional de que F_0 == 0
 * e que F_{n-1} == 1; mas os demais valores coincidem com
 * a definição usual de Fibonacci.)
 * Em essência, o problema pede F_n.
 *
 * Entretanto, n pode ser até 10^10^6,
 * portanto mesmo exponenciação modular é muito lenta.
 * Precisamos de outra ideia.
 *
 * Como estamos trabalhando em (Z_1000)^2,
 * existem exatamente 10^6 valores diferentes de fib.
 * Pelo princípio do pombal, eventualmente next^n irá se tornar cíclico;
 * e este ciclo possui período inferior a 10^6.
 * Iremos nos basear nesta observação
 * para obter um algoritmo com complexidade linear,
 * mas uma constante mais baixa que exponenciação modular.
 *
 * Suponha que este ciclo seja "completo"; quero dizer,
 * next^m(base) = base para algum m.
 * Neste caso, next^k(base) == next^(k % m)(base);
 * portanto, na entrada n, basta computar n % m
 * e usar exponenciação modular para obter F_{n % m}.
 *
 * next é uma operação inversível, portanto,
 * caso o primeiro valor a se repetir fosse (digamos) t,
 * teríamos next^t == next^(t+m);
 * aplicando next^(-1), a inversa de next,
 * concluímos que next^(t-1) == next^(t+m-1), contradição.
 * Portanto, t = 0.
 *
 * Como iremos calcular m no começo da execução do programa,
 * também deixaremos pré-computado next^k(base)
 * para 0 <= k < m.
 *
 * Por último, temos que calcular n % m.
 * Como n pode ter 10^6 dígitos,
 * não podemos lê-lo num inteiro;
 * leremos-no para uma string e calcularemos este valor diretamente.
 * Para isso, usaremos uma técnica baseada em autômatos finitos.
 *
 * Crie a variável i. Imporemos sobre i a invariante de que,
 * se N é o número formado pelos dígitos lidos até agora,
 * então i == N % m.
 * Para a primeira iteração, i == primeiro dígito % m.
 * Ao avançar para a iteração n+1, basta multiplicar i por 10 e somar o dígito n+1.
 * Após extrair o módulo, manteremos a invariante.
 *
 * Ao final do laço, basta retornar o valor lido.
 */
#include <stdio.h>
#include <utility>

int next( int f ) {
    int a = f / 1000;
    int b = f % 1000;
    return (a + b) % 1000 * 1000 + a;
}

int nfib[(int)1e6]; // nfib[i] == next(nfib[i-1])
int modulo = 0; // o m discutido acima

void fib_precalc() {
    nfib[0] = 1;
    modulo++;
    for( int i = 1; i < 1e6; i++ ) {
        nfib[i] = next(nfib[i-1]);
        if( nfib[i] == 1 )
            break;

        modulo++;
    }
}

int solve( const char * str ) {
    int i = *str - '0';
    while( *++str != '\0' )
        i = (10*i + *str - '0') % modulo;

    return nfib[i] / 1000;
}

char str[(int) 1e6+2];
int main() {
    fib_precalc();
    int n;
    scanf( "%d", &n );
    while( n-- ) {
        scanf( "%s", str );
        printf( "%03d\n", solve(str) );
    }
    return 0;
}

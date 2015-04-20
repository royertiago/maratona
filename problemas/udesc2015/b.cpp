/* Problema B da seletiva doméstica da UDESC de 2015.
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <climits> // CHAR_BIT

std::string source, target;

int dp[1 << 18];
/* Esta programação dinâmica será indexada por máscaras de bits.
 * Cada máscara indicará quais os índices da palavra de destino
 * já foram obtidos. Por exemplo, se target == "ACTG",
 * então index == 10 == 0b1010 representa o estado "A.T.".
 * dp[bitmask] é a menor quantidade de movimentos necessários
 * para chegar de source até o estado representado por bitmask,
 * ou -1 se não estiver inicializado.
 *
 * Para computar o valor de um índice, iteraremos sobre todos os seus
 * subconjuntos e consideraremos apenas aqueles que podem chegar
 * até o índice atual em exatamente uma operação.
 * O valor deste índice será, portanto, o mínimo destes conjuntos
 * somado de 1.
 */

/* Uma instância só é não-resolvível se target possuir alguma
 * base nitrogenada que source não possua.
 * Caso contrário, sempre podemos copiar uma letra de cada vez,
 * embora este procedimento não gere, necessariamente, o melhor resultado.
 */
bool solvable() {
    return target.find_first_not_of(source) == std::string::npos;
}

/* Retorna a distância entre source e o estado representado por bitmask.
 */
int solve( int bitmask );

/* Verdadeiro caso seja possível gerar a string str a partir do estado atual,
 * e falso caso contrário.
 */
bool produces( int bitmask, std::string str );

int solve() {
    for( int i = 0; i < 1 << target.size(); i++ )
        dp[i] = -1;
    dp[0] = 0;
    return solve( (1 << target.size()) - 1 );
}

int solve( int bitmask ) {
    if( dp[bitmask] != -1 ) return dp[bitmask];

    int lower_bit = __builtin_ctz( bitmask );
    int upper_bit = sizeof(int) * CHAR_BIT - __builtin_clz( bitmask ) - 1;
    int min = target.size();
    for( int i = lower_bit; i <= upper_bit; i++ )
        for( int j = i; j <= upper_bit; j++ ) {
            int window = (1 << (j + 1)) - (1 << i);
            /* window é uma máscara que tem os bits i, i+1, ..., j ligados,
             * e os demais desligados.
             * Iremos iterar apenas sobre as submáscaras "contínuas" de bitmask;
             * quero dizer, apenas as submáscaras s tais que
             * s | window == bitmask, e s & window == 0.
             * Observe que outras submáscaras não podem chegar até esta máscara
             * através de apenas um movimento.
             */
            if( (bitmask & window) != window )
                /* window não é um subconjunto de bitmask. */
                continue;

            std::string substr = target.substr(i, j - i + 1);
            if( produces(bitmask - window, substr) ) {
                min = std::min( min, solve(bitmask - window) );
            }
        }

    return dp[bitmask] = min + 1;
}

bool produces( int bitmask, std::string str ) {
    std::string masked = target;
    for( char & c : masked ) {
        if( (bitmask & 1) == 0 )
            c = '.';
        bitmask >>= 1;
    }
    std::string rev( str.rbegin(), str.rend() );
    return masked.find(str) != std::string::npos
        || masked.find(rev) != std::string::npos
        || source.find(str) != std::string::npos
        || source.find(rev) != std::string::npos;
}

int main() {
    int n;
    std::cin >> n;
    while( n-- ) {
        std::cin >> source >> target;
        if( solvable() ) {
            std::cout << solve() << std::endl;
        }
        else
            std::cout << "IMPOSSIVEL\n";
    }
    return 0;
}

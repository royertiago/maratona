/* Problema B da seletiva doméstica da UDESC de 2015.
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
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

/* Defina str = target[i, i+1, ..., j], rev = target[j, j-1, ..., i].
 * Verdadeiro caso seja possível gerar str ou rev a partir do estado atual,
 * e falso caso contrário.
 */
bool produces( int bitmask, int i, int j );

bool source_substr[18][18];
/* Estrutura de dados para acelerar a consulta a produces.
 * source_substr[i][j] é verdadeiro se e somente se
 * ou target[i, i+1, ..., j] for uma substring de source
 * ou target[j, j-1, ..., i] for.
 *
 * Esta estrutura será precomputada no começo da execução do algoritmo
 * e permitirá consulta em O(1) à primeira metade do produces:
 * determinar se dá para gerar str a partir de source.
 */

int lower_mask[1 << 9][18][18];
bool upper_mask[1 << 9][18][18];
int lower_mask_r[1 << 9][18][18];
bool upper_mask_r[1 << 9][18][18];
/* Estruturas de dados para acelerar a segunda metade do produces.
 * Divida a máscara atual em duas: upper e lower, cada uma com metade dos bits
 * --- convencionaremos deixar lower com mais bits se a divisão não for exata.
 * lower_mask[lower][i][j] codificará informações a respeito da construtibilidade
 * de target[i, i+1, ..., j] a partir de target, quando target estiver mascarado
 * por uma máscara de bits cujos bits inferiores forem lower.
 *
 * Chame str = target[i, i+1, ..., j]
 *
 * lower_mask[lower][i][j] == 0 indica que é possível construir str a partir
 * daquela máscara, independente de qual forem os bits superiores.
 * Isso só é possível se a máscara inferior for suficiente
 * para construir str sozinha.
 *
 * Se lower_mask[lower][i][j] == k com k > 0, queremos indicar que
 * não dá para construir str usando apenas os bits inferiores,
 * mas dá para começar a construir str usando os bits inferiores
 * e faltam exatamente k caracteres de str, que devem estar presentes
 * na máscara superior.
 *
 * Caso não dê nem para começar a construir str,
 * então lower_mask[lower][i][j] == -1.
 *
 * Para upper_mask[upper][i][j], apenas precisamos codificar a informação
 * de que é possível construir str a partir da máscara usando os bits superiores
 * da máscara, portanto upper_mask é um booleano.
 *
 * lower_mask_r e upper_mask_r são análogos, mas para str == target[j, j-1, ..., i].
 */
int lower_mask_size;
int upper_mask_size;

void precompute_masks() {
    lower_mask_size = (target.size() + 1)/2;
    upper_mask_size = target.size() - lower_mask_size;

    for( int lower = 0; lower < (1 << lower_mask_size); lower++ )
    for( int i = 0; i < target.size(); i++ )
    for( int j = i; j < target.size(); j++ ) {
        int lower_tmp = lower;
        std::string target_tmp = target;
        std::string str = target.substr(i, j - i + 1);
        std::string rev( str.rbegin(), str.rend() ); // reverse string

        std::string::iterator it = target_tmp.begin();
        for( int k = 0; k < lower_mask_size; ++k, ++it, lower_tmp >>= 1 )
            if( (lower_tmp & 1) == 0 )
                *it = '.';

        int index = target_tmp.find(str);
        if( index == std::string::npos || index >= lower_mask_size )
            lower_mask[lower][i][j] = -1;
        else if( index + str.size() <= lower_mask_size )
            lower_mask[lower][i][j] = 0;
        else
            lower_mask[lower][i][j] = index + str.size() - lower_mask_size;

        index = target_tmp.find(rev);
        if( index == std::string::npos || index >= lower_mask_size )
            lower_mask_r[lower][i][j] = -1;
        else if( index + str.size() <= lower_mask_size )
            lower_mask_r[lower][i][j] = 0;
        else
            lower_mask_r[lower][i][j] = index + str.size() - lower_mask_size;
    }

    for( int upper = 0; upper < (1 << upper_mask_size); upper++ )
    for( int i = 0; i < target.size(); i++ )
    for( int j = i; j < target.size(); j++ ) {
        int upper_tmp = upper;
        std::string target_tmp = target;
        std::string str = target.substr(i, j - i + 1);
        std::string rev( str.rbegin(), str.rend() ); // reverse string

        std::string::iterator it = target_tmp.begin() + lower_mask_size;
        for( int k = 0; k < upper_mask_size; ++k, ++it, upper_tmp >>= 1 )
            if( (upper_tmp & 1) == 0 )
                *it = '.';

        upper_mask[upper][i][j] =
            target_tmp.find(str, lower_mask_size) != std::string::npos;
        upper_mask_r[upper][i][j] =
            target_tmp.find(rev, lower_mask_size) != std::string::npos;
    }
}

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

int solve() {
    for( int i = 0; i < 1 << target.size(); i++ )
        dp[i] = -1;
    dp[0] = 0;

    for( int i = 0; i < target.size(); i++ )
        for( int j = i; j < target.size(); j++ ) {
            std::string str = target.substr(i, j - i + 1);
            std::string rev( str.rbegin(), str.rend() );
            source_substr[i][j] = source.find(str) != std::string::npos
                || source.find(rev) != std::string::npos;
        }

    precompute_masks();

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

            if( produces(bitmask - window, i, j) ) {
                min = std::min( min, solve(bitmask - window) );
            }
        }

    return dp[bitmask] = min + 1;
}

bool produces( int bitmask, int i, int j ) {
    if( source_substr[i][j] )
        return true;
    if( __builtin_popcount(bitmask) < j - i + 1 )
        return false;

    int lower = bitmask & ((1 << lower_mask_size) - 1);
    int upper = bitmask >> lower_mask_size;
    int shift;

    /* Primeiro, tentaremos construir a substring na orientação correta;
     * depois, tentaremos construir invertido. */
    if( upper_mask[upper][i][j] )
        return true;
    if( lower_mask[lower][i][j] == -1 )
        goto reverse_construct; // porque foda-se o Melga

    shift = (1 << lower_mask[lower][i][j]) - 1;
    if( (upper & shift) == shift )
        /* shift está toda contida em upper;
         * isto significa que os lower_mask[lower][i][j] bits inferiores
         * de upper estão em 1. Portanto, podemos construir str usando bitmask.
         */
        return true;

reverse_construct:
    if( upper_mask_r[upper][i][j] )
        return true;
    if( lower_mask_r[lower][i][j] == -1 )
        return false;

    shift = (1 << lower_mask_r[lower][i][j]) - 1;
    if( (upper & shift) == shift )
        return true;

    return false;
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

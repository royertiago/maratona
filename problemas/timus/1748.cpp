/* 1748.cpp
 * Problema: http://acm.timus.ru/problem.aspx?num=1748
 *
 * Números altamente compostos:
 * http://en.wikipedia.org/wiki/Highly_composite_number
 * 
 * Se escrevermos um número altamente composto A como
 * A == 2^e1 * 3^e2 * 5^e3...
 * vemos que, caso algum ei seja maior que ej com i > j, podemos
 * inverter os expoentes para produzir um número menor, com a mesma quantidade
 * de divisores que o número anterior. Portanto, e1 >= e2 >= e3 >= ...
 *
 * Números deste tipo (com sequência não-crescente de expoentes) crescem
 * rapidamente - existem 32739 deles entre 1 e 10^18 - então é viável
 * gerar todos eles, selecionar apenas os altamente compostos e fazer
 * buscas binárias na base de dados recém criada. */
#include <stdio.h>
#include <vector>
#include <algorithm>

#define MAX 1000000000000000000 // 10^18
#define LOG2_MAX 60
typedef long long unsigned llu;

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
/* Como 2*3*5*...*47 < MAX < 2*3*5*...*47*53, os únicos números que têm
 * chance de serem altamente compostos possuem fatores primos menores
 * ou iguais a 47. */

llu max_before[15];
/* max_before[k] é o maior valor tal que max_before[k]*prime[k] <= MAX */

struct hcn_t {
    llu value;
    llu divisors;
    bool operator<( hcn_t h ) const {
        return value < h.value;
    }
};

std::vector<hcn_t> candidates, hcn;

/* pi é o índice do próximo primo a ser usado, pmax é o maior
 * valor do espoente deste primo de forma a manter a propriedade
 * de decrescer os índices. */
void precompute( llu current, int pi, int pmax, llu divisors ) {
    for( int i = 1; i <= pmax && current <= max_before[pi]; ++i ) {
        current *= primes[pi];
        candidates.push_back({ current, divisors * (i + 1) });
        precompute( current, pi+1, i, divisors * (i+1) );
    }
}

int main() {
    for( int i = 0; i < 15; ++i )
        max_before[i] = (MAX + primes[i] - 1)/primes[i];
    candidates.push_back({1, 1});
    precompute( 1, 0, LOG2_MAX, 1 );

    std::sort( candidates.begin(), candidates.end() );
    unsigned max_divisors = 0;
    for( hcn_t number : candidates )
        if( number.divisors > max_divisors ) {
            max_divisors = number.divisors;
            hcn.push_back( number );
        }

    llu C, N;
    scanf( "%llu", &C );
    while( C-- ) {
        scanf( "%llu", &N );
        auto it = --std::upper_bound( hcn.begin(), hcn.end(), hcn_t{N, 0} );
        printf( "%llu %llu\n", it->value, it->divisors );
    }
    return 0;
}

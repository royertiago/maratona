/* 2191.cpp
 * Problema: http://acm.cs.ecnu.edu.cn/problem.php?problemid=2191
 * Mirror: http://acm.tju.edu.cn/toj/showp3349.html
 * Mirror: https://code.google.com/codejam/contest/32015/dashboard#s=p2
 */
#include <stdio.h>
#include <algorithm>

#define MAX 500*1000
#define MOD 1000000007
typedef long long unsigned llu;

struct index_pair {
    unsigned limit, index;
    bool operator<( index_pair p ) const {
        if( limit != p.limit ) return limit < p.limit;
        return index > p.index;
    }
} limits[MAX];

llu n, m, X, Y, Z;
unsigned A[100];

int fenwick[MAX+1];
/* Construiremos uma árvore de Fenwick para contar todas as possíveis
 * sequências de limites crescentes de velocidade.
 * Note que a árvore é indexada em 1; index_pair::index corresponde a
 * um índice nesta árvore. */
int get( unsigned i ) {
    int value = fenwick[i];
    while( (i -= i & -i) != 0 )
        value = (value + fenwick[i]) % MOD;
    return value;
}
void set( unsigned i, int value ) {
    do
        fenwick[i] = (fenwick[i] + value) % MOD;
    while( (i += i & -i) <= n );
}

int solve() {
    for( unsigned i = 0; i <= n; ++i ) fenwick[i] = 0;

    std::sort( limits, limits + n );

    for( unsigned i = 0; i < n; ++i )
    /* Ordenamos o vetor para garantir a seguinte afirmação: em cada iteração,
     * p.limit é o maior limite de velocidade já estudado no intervalo
     * [1, p.index]. E por "maior", queremos dizer "estritamente maior".
     * Isso é garantido pela função de ordenação.
     *
     * A invariante a ser mantida é: na iteração i, todos os limites de 
     * velocidade que envolvem as placas limits[0], limits[1], ..., limits[i]
     * estão na árvore; isto é, get(j) retorna a quantidade de sequências
     * crescentes usando as placas com índices [1, 2, ..., j] que já foram
     * analisadas pelo programa. */
        set( limits[i].index, get(limits[i].index) + 1 );
    /* Ao analisar a placa no índice p.index, podemos adicionar mais exatamente
     * get(p.index) + 1 sequências crescentes: uma para cada sequência já
     * existente usando as placas de índices [1, 2, ..., p.index], e mais
     * uma sequência que contém apenas a placa p.index.
     * Sabemos que nenhuma placa com índice [1, 2, ..., p.index-1] foi 
     * analisada por causa da ordenação imposta acima. */

    return get( n );
}

int main() {
    int N;
    scanf( "%d", &N );
    for( int t = 1; t <= N; ++t ) {
        scanf( "%llu%llu%llu%llu%llu", &n, &m, &X, &Y, &Z );
        for( unsigned j = 0; j < m; ++j )
            scanf( "%u", &A[j] );

        for( unsigned i = 0; i < n; ++i ) {
            limits[i] = {A[i % m], i+1};
            A[i % m] = (X * A[i % m] + Y * (i + 1)) % Z;
        }
        printf( "Case #%i: %d\n", t, solve() );
    }
    return 0;
}

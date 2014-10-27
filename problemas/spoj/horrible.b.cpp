/* horrible.a.cpp
 * Problema: http://br.spoj.com/problems/HORRIBLE/
 *
 * Árvore de segmentos.
 */
#include <stdio.h>
#include <limits.h>
#include <algorithm>

#define MAX2 131072

typedef long long ll;

int first_power( unsigned i ) {
    return 1 << CHAR_BIT * sizeof(unsigned) - __builtin_clz(i - 1);
}

/* Árvore de segmentos sobre o tipo T, com a operação op.
 * Hipóteses: (defina apply(T, U) == apply(T, U, 1)).
 *  - data_merge é associativo e data_identity é sua identidade;
 *  - op_merge é associativo, comutativo e op_identity é sua identidade;
 *  - apply(T, op_identity) == T;
 *  - apply(apply(T, U), V) == apply(T, op_merge(U, V));
 *  - apply(merge(T1, T2, T3, ..., TN), U, n) == 
 *      merge(apply(T1, U), apply(T2, U), ..., apply(TN, U)). */
template< typename T, typename U >
struct segment_tree {
    T (*data_merge)(T, T);
    T data_identity;
    U (*op_merge)(U, U);
    U op_identity;
    T (*apply)(T, U, unsigned);

    unsigned size;
    T data[2*MAX2];
    U lazy[2*MAX2];

    /* Reinicia a árvore. A árvore conterá tamanho new_size
     * e a posição i da árvore conterá o elemento generator(i). */
    void reset( unsigned new_size, T (*generator)(unsigned) ) {
        size = new_size;
        reset( 1, size, 1, generator );
    }

    /* Executa v[a] = op(v[a], value) para cada a no intervalo [min, max].
     * Assume-se que 1 <= min <= max <= size. */
    void update( int min, int max, U value ) {
        update( min, max, 1, size, 1, value );
    }

    /* Retorna op(min, min+1, min+2, ..., max).
     * Assume-se que 1 <= min <= max <= size. */
    T query( unsigned min, unsigned max ) {
        return query( min, max, 1, size, 1 );
    }

    /* Reinicia todos os nodos abaixo do nodo index e retorna o valor
     * armazenado neste nodo. */
    T reset( int smin, int smax, int index, T (*gen)(unsigned) ) {
        int middle = (smin + smax)/2;
        lazy[index] = op_identity;
        if( smin == smax )
            return data[index] = gen(smin);
        return data[index] = data_merge(
            reset( smin, middle, 2*index, gen ),
            reset( middle+1, smax, 2*index+1, gen )
        );
    }

    /* Faz a atualização no intervalo e retorna o valor armazenado. */
    T update( int min, int max, int smin, int smax, int index, U value ) {
        int middle = (smin + smax)/2;
        if( min == smin && max == smax ) {
            lazy[index] = op_merge( lazy[index], value );
            return data[index] = apply( data[index], value, max - min + 1 );
        }
        T left = data[2*index], right = data[2*index+1];
        if( min <= middle )
            left = update( min, std::min(max, middle), smin, middle, 2*index, value );
        if( max >= middle + 1)
            right = update( std::max(min, middle+1), max, middle+1, smax, 2*index + 1, value );
        data[index] = apply( data_merge(left, right), lazy[index], smax - smin + 1 );
        return data[index];
    }

    /* Retorna o valor da consulta no intervalo. */
    T query( int min, int max, int smin, int smax, int index ) {
        int middle = (smin + smax)/2;
        if( min == smin && max == smax )
            return data[index];
        T left = data_identity, right = data_identity;
        if( min <= middle )
            left = query( min, std::min(max, middle), smin, middle, 2*index );
        if( max >= middle + 1 )
            right = query( std::max(min, middle+1), max, middle+1, smax, 2*index + 1 );
        T ret = apply( data_merge(left, right), lazy[index], max - min + 1 );
        return ret;
    }
};
int N, C;

ll sum( ll a, ll b ) { return a + b; }
ll apply( ll a, ll b, unsigned n ) { return a + n * b; }
ll gen( unsigned ) { return 0; }

int main() {
    segment_tree< ll, ll > tree;
    tree.data_merge = tree.op_merge = sum;
    tree.apply = apply;
    tree.data_identity = tree.op_identity = 0;
    int cases;
    scanf( "%d", &cases );
    while( cases-- ) {
        scanf("%d%d", &N, &C);
        tree.reset( N, gen );
        while( C-- ) {
            int t, a, b, v;
            scanf( "%d", &t );
            if( t == 0 ) {
                scanf( "%d%d%d", &a, &b, &v );
                tree.update( a, b, v );
            } else {
                scanf( "%d%d", &a, &b );
                printf( "%lld\n", tree.query(a, b) );
            }
        }
    }
    return 0;
}

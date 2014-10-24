/* horrible.a.cpp
 * Problema: http://br.spoj.com/problems/HORRIBLE/
 *
 * Árvore de segmentos.
 */
#include <stdio.h>
#include <limits.h>

#define MAX2 131072

typedef long long ll;

int first_power( unsigned i ) {
    return 1 << CHAR_BIT * sizeof(unsigned) - __builtin_clz(i - 1);
}

/* Árvore de segmentos sobre o tipo T, com a operação op.
 * Hipóteses: op(a, b)        == op(b, a)            (comutatividade)
 *            op(a, op(b, c)) == op(op(a, b), c)     (associatividade)
 *            op(a, identity) == a                   (existência de identidade)
 *            op(a, b, n+1)   == op(op(a, b), b, n),
 *            op(a, b, 0)     == a                   (multiplicidade) */
template< typename T >
struct segment_tree {
    static T identity;
    static T (*op)(T, T);
    static T (*op_n)(T, T, unsigned);

    /* Reinicia a árvore. A árvore conterá tamanho size
     * e será iniciada apenas com identity. */
    void reset( unsigned size ) {
        for( int i = 1; i < 2*first_power(size); ++i )
            data[i] = lazy[i] = identity;
        this->size = size;
    }

    /* Executa v[a] = op(v[a], value) para cada a no intervalo [min, max].
     * Assume-se que 1 <= min <= max <= size. */
    void update( int min, int max, T value ) {
        update( min, max, 1, size, 1, value );
    }

    /* Retorna op(min, min+1, min+2, ..., max).
     * Assume-se que 1 <= min <= max <= size. */
    T query( unsigned min, unsigned max ) {
        return query( min, max, 1, size, 1 );
    }

    unsigned size;
    T data[2*MAX2];
    T lazy[2*MAX2];
    /* Fz a propagação da atualização no intervalo.
     * index é o nodo atual, e smin e smax (segment min, segment max)
     * são as extremidades do segmento de domíno do nodo.
     * Isto é, o nodo index controla o segmento [smin, smax].
     * Assume-se que smin <= min <= max <= smax. */
    void update( int min, int max, int smin, int smax, int index, T value ) {
        int middle = (smin + smax)/2;
        data[index] = op_n( data[index], value, max - min + 1 );
        if( min == smin && max == smax )
            lazy[index] = op( lazy[index], value );
        else if( max <= middle )
            update( min, max, smin, middle, 2*index, value );
        else if( min >= middle + 1 )
            update( min, max, middle+1, smax, 2*index + 1, value );
        else {
            update( min,      middle, smin,     middle, 2*index,     value );
            update( middle+1, max,    middle+1, smax,   2*index + 1, value );
        }
    }
    
    T query( int min, int max, int smin, int smax, int index ) {
        int middle = (smin + smax)/2;
        T lazy_value = op_n( identity, lazy[index], max - min + 1 );
        if( min == smin && max == smax )
            return data[index]; // Note que não precisamos de lazy_value
        if( max <= middle )
            return lazy_value + query( min, max, smin, middle, 2*index );
        if( min >= middle + 1 )
            return lazy_value + query( min, max, middle+1, smax, 2*index + 1 );
        return lazy_value + query( min, middle, smin, middle, 2*index ) +
            query( middle+1, max, middle+1, smax, 2*index + 1);
    }
};
template< typename T >
T (*segment_tree< T >::op)(T, T);
template< typename T >
T (*segment_tree< T >::op_n)(T, T, unsigned);
template< typename T >
T segment_tree< T >::identity;

segment_tree< ll > tree;
int N, C;

ll op( ll a, ll b ) { return a + b; }
ll op_n( ll a, ll b, unsigned n ) { return a + n * b; }

int main() {
    segment_tree< ll >::op = op;
    segment_tree< ll >::op_n = op_n;
    segment_tree< ll >::identity = 0;

    int cases;
    scanf( "%d", &cases );
    while( cases-- ) {
        scanf("%d%d", &N, &C);
        tree.reset( N );
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

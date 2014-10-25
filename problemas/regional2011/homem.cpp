/* homem.cpp
 * Problema: http://br.spoj.com/problems/HOMEM/
 */
#include <stdio.h>
#include <limits.h>
#include <algorithm>

#define MAX2 131072

int next_power( unsigned i ) {
    return 1 << CHAR_BIT*sizeof(unsigned) - __builtin_clz(i-1);
}

template< typename T, typename U >
struct segment_tree {
    T (*data_merge)(T, T);
    U (*op_merge)(U, U);
    T (*apply)(T, U, unsigned);
    T data_identity;
    U op_identity;

    T data[2*MAX2];
    U lazy[2*MAX2];
    unsigned size;
    void reset( unsigned new_size, T (*generator)(int) ) {
        size = new_size;
        build( 1, size, 1, 1, generator );
    }

    void update( int min, int max, U value ) {
        update( min, max, 1, size, 1, value );
    }

    T query( int min, int max ) {
        return query( min, max, 1, size, 1 );
    }

    T build( int smin, int smax, int index, int source_index, T (*gen)(int) ) {
        lazy[index] = op_identity;
        int middle = (smin + smax)/2;
        if( smin == smax )
            return data[index] = gen(source_index);

        return data[index] = data_merge(
                build( smin, middle, 2*index, source_index, gen ),
                build( middle+1, smax, 2*index + 1, middle+1, gen )
        );
    }

    T update( int min, int max, int smin, int smax, int index, U value ) {
        int middle = (smin + smax)/2;
        if( min == smin && max == smax ) {
            lazy[index] = op_merge( lazy[index], value );
            return data[index] = apply( data[index], value, max - min + 1 );
        }
        T left = data[2*index], right = data[2*index+1];
        if( min >= smin && min <= middle )
            left = update( min, std::min(max, middle), smin, middle, 2*index, value );
        if( max <= smax && max >= middle + 1)
            right = update( std::max(min, middle+1), max, middle+1, smax, 2*index + 1, value );
        return data[index] = apply( data_merge(left, right), lazy[index], smax - smin + 1 );
    }

    T query( int min, int max, int smin, int smax, int index ) {
        int middle = (smin + smax)/2;
        if( min == smin && max == smax )
            return data[index];
        T left = data_identity, right = data_identity;
        if( min >= smin && min <= middle )
            left = query( min, std::min(max, middle), smin, middle, 2*index );
        if( max <= smax && max >= middle + 1 )
            right = query( std::max(min, middle+1), max, middle+1, smax, 2*index + 1 );
        return apply( data_merge(left, right), lazy[index], max - min + 1 );
    }
};

struct her {
    int h, e, r;
    her rotate() {
        return (her) {r, h, e};
    }
};

her op( her a, her b ) {
    return (her) {a.h + b.h, a.e + b.e, a.r + b.r};
}
unsigned op( unsigned a, unsigned b ) {
    return a + b;
}
her apply( her a, unsigned b, unsigned ) {
    b %= 3;
    if( b > 0 ) {
        a = a.rotate();
        b--;
    }
    if( b > 0 )
        a = a.rotate();
    return a;
}
her gen( int ) {
    return (her) {1, 0, 0};
}

segment_tree< her, unsigned > tree;

int main() {
    tree.data_merge = op;
    tree.op_merge = op;
    tree.apply = apply;
    tree.data_identity = (her) {0, 0, 0};
    tree.op_identity = 0;

    int N, Q;
    char str[2];
    while( scanf("%d%d", &N, &Q) != EOF ) {
        tree.reset( N, gen );
        int i, j;
        while( Q-- ) {
            scanf( "%s%d%d", str, &i, &j );
            if( str[0] == 'M' )
                tree.update( i, j, 1 );
            else {
                her t = tree.query( i, j );
                printf( "%d %d %d\n", t.h, t.e, t.r );
            }
        }
        printf( "\n" );
    }
    return 0;
}

/* brckts.cpp
 * Problema: http://www.spoj.com/problems/BRCKTS/
 *
 * Árvore de segmentos, sem lazy propagation.
 */
#include <stdio.h>
#include <limits.h>
#include <algorithm>

#define MAX2 32768

// Árvore de segmentos sem lazy propagation.
template< typename T, typename U >
struct segment_tree {
    T (*data_merge)(T, T);
    T data_identity;
    T (*apply)(T, U);

    unsigned size;
    T data[2*MAX2];

    void reset( unsigned new_size, T (*generator)(unsigned) ) {
        size = new_size;
        reset( 1, size, 1, generator );
    }

    void update( int min, int max, U value ) {
        update( min, max, 1, size, 1, value );
    }

    T query( unsigned min, unsigned max ) {
        return query( min, max, 1, size, 1 );
    }

    T reset( int smin, int smax, int index, T (*gen)(unsigned) ) {
        int middle = (smin + smax)/2;
        if( smin == smax )
            return data[index] = gen(smin);
        return data[index] = data_merge(
            reset( smin, middle, 2*index, gen ),
            reset( middle+1, smax, 2*index+1, gen )
        );
    }

    T update( int min, int max, int smin, int smax, int index, U value ) {
        int middle = (smin + smax)/2;
        if( min == smin && max == smax ) {
            return data[index] = apply( data[index], value );
        }
        T left = data[2*index], right = data[2*index+1];
        if( min >= smin && min <= middle )
            left = update( min, std::min(max, middle), smin, middle, 2*index, value );
        if( max <= smax && max >= middle + 1)
            right = update( std::max(min, middle+1), max, middle+1, smax, 2*index + 1, value );
        return data[index] = merge( left, right );
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
        return data_merge(left, right);
    }
};

struct word {
    int l; // left brackets
    int r; // right brackets
};

word merge( word l, word r ) {
    return (word) {l.l + r.l - std::min(l.r, r.l),
            r.r + l.r - std::min(l.r, r.l)};
}

char str[30000+1];
word gen( unsigned i ) {
    if( str[i-1] == ')' ) return (word) {1, 0};
    return (word) {0, 1};
}

word apply( word a, int ) {
    return (word) {a.r, a.l};
}

int main() {
    segment_tree< word, int > tree;
    tree.data_merge = merge;
    tree.data_identity = (word) {0, 0};
    tree.apply = apply;

    int C = 1, size;
    while( scanf("%d\n", &size) != EOF ) {
        scanf( "%s", str );
        printf( "Test %i:\n", C++ );
        tree.reset( size, gen );
        int Q;
        scanf( "%d", &Q );
        while( Q-- ) {
            int t;
            scanf( "%d", &t );
            if( t == 0 ) {
                word w = tree.query( 1, size );
                if( w.l == 0 && w.r == 0 )
                    printf( "YES\n" );
                else
                    printf( "NO\n" );
            } else {
                tree.update( t, t, 1 );
            }
        }
    }
    return 0;
}

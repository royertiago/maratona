/* naw.b.cpp
 * Problema da Algorithmic Engagements 2003.
 * Mirror: http://www.spoj.com/problems/BRCKTS/
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
    T data[2*MAX2];
    T (*merge)( T, T );
    T identity;
    T (*apply)( T, U );
    int size;

    void reset( int new_size, T (*gen)(unsigned) ) {
        size = new_size;
        reset( 1, size, 1, gen );
    }
    T query( int min, int max ) {
        return query( min, max, 1, size, 1 );
    }
    void update( int i, U value ) {
        update( i, 1, size, 1, value );
    }

    T reset( int smin, int smax, int index, T (*gen)(unsigned) ) {
        int middle = (smin + smax)/2;
        if( smin == smax )
            return data[index] = gen(smin);

        return data[index] = merge( 
            reset(smin, middle, 2*index, gen),
            reset(middle+1, smax, 2*index+1, gen)
        );
    }
    T query( int min, int max, int smin, int smax, int index ) {
        int middle = (smin + smax)/2;
        if( min == smin && max == smax )
            return data[index];
        T left = identity, right = identity;
        if( min <= middle )
            left = query( min, std::min(max, middle), smin, middle, 2*index);
        if( max >= middle + 1 )
            right = query( std::max(min, middle+1), max, middle+1, smax, 2*index+1 );
        return merge(left, right);
    }
    T update( int i, int smin, int smax, int index, U value ) {
        int middle = (smin + smax)/2;
        if( smin == smax )
            return data[index] = apply(data[index], value);
        T left = data[2*index], right = data[2*index+1];
        if( i <= middle )
            left = update( i, smin, middle, 2*index, value );
        if( i >= middle + 1 )
            right = update( i, middle+1, smax, 2*index+1, value );
        return data[index] = merge(left, right);
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
    tree.merge = merge;
    tree.identity = (word) {0, 0};
    tree.apply = apply;

    int size;
    scanf( "%d%s\n", &size, str );
    tree.reset( size, gen );
    int Q;
    scanf( "%d", &Q );
    while( Q-- ) {
        int t;
        scanf( "%d", &t );
        if( t == 0 ) {
            word w = tree.query( 1, size );
            if( w.l == 0 && w.r == 0 )
                printf( "TAK\n" );
            else
                printf( "NIE\n" );
        } else {
            tree.update( t, 1 );
        }
    }
    return 0;
}

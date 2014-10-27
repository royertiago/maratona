/* I.cpp
 * Problema da etapa nacional da Maratona de 2012.
 * Mirror: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3977
 *
 * Árvore de segmentos.
 */
#include <stdio.h>
#include <algorithm>
#define MAX2 131072 // 2^17 > 10^5

template< typename T, typename U >
struct segment_tree {
    T data[2*MAX2];
    T (*merge)( T, T );
    T identity;
    T (*apply)( T, U );
    int size;

    void rebuild( const T * source, int new_size ) {
        size = new_size;
        rebuild( 1, size, 1, source );
    }
    T query( int min, int max ) {
        return query( min, max, 1, size, 1 );
    }
    void update( int i, U value ) {
        update( i, 1, size, 1, value );
    }

    T rebuild( int smin, int smax, int index, const T * source ) {
        int middle = (smin + smax)/2;
        if( smin == smax )
            return data[index] = source[smin];

        return data[index] = merge( 
            rebuild(smin, middle, 2*index, source),
            rebuild(middle+1, smax, 2*index+1, source)
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

char merge( char a, char b ) {
    if( a == '0' || b == '0' )
        return '0';
    if( a == '+' && b == '-' || a == '-' && b == '+' )
        return '-';
    return '+';
}

char to_char( int i ) {
    if( i == 0 ) return '0';
    if( i > 0 ) return '+';
    return '-';
}

char apply( char, char a ) {
    return a;
}

int main() {
    segment_tree<char, char> tree;
    tree.merge = merge;
    tree.apply = apply;
    tree.identity = '+';
    char origin[100*1000+1];
    int N, K;
    while( scanf("%d%d", &N, &K) != EOF ) {
        int a, b; char op[2];
        for( int i = 1; i <= N; ++i ) {
            scanf( "%d", &a );
            origin[i] = to_char(a);
        }
        tree.rebuild( origin, N );
        while( K-- ) {
            scanf( "%s%d%d", op, &a, &b );
            if( op[0] == 'P' )
                printf( "%c", tree.query( a, b ) );
            else
                tree.update( a, to_char(b) );
        }
        printf( "\n" );
    }
    return 0;
}

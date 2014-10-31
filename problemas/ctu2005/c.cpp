/* c.cpp
 * Problema C da competição CTU Open 2005.
 * Mirror: http://poj.org/problem?id=2991
 *
 * Árvore de segmentos.
 */
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <algorithm>

#define PI 3.14159265358979323846264338327950
#define MAX  10000
#define MAX2 16384

// Árvore de segmentos, sem lazy propagation.
template< typename T, typename U >
struct segment_tree {
    T (*merge)(T, T);
    T identity;
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
        return data[index] = merge(
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
        if( min <= middle )
            left = update( min, std::min(max, middle), smin, middle, 2*index, value );
        if( max >= middle + 1)
            right = update( std::max(min, middle+1), max, middle+1, smax, 2*index + 1, value );
        return data[index] = merge( left, right );
    }

    T query( int min, int max, int smin, int smax, int index ) {
        int middle = (smin + smax)/2;
        if( min == smin && max == smax )
            return data[index];
        T left = identity, right = identity;
        if( min <= middle )
            left = query( min, std::min(max, middle), smin, middle, 2*index );
        if( max >= middle + 1 )
            right = query( std::max(min, middle+1), max, middle+1, smax, 2*index + 1 );
        return merge(left, right);
    }
};

struct crane {
    double x, y; // end point
    double end_angle;
    crane() {}
    crane( double x, double y, double end_angle ) :
        x(x), y(y), end_angle(end_angle) {}
};

crane merge( crane a, crane b ) {
    double x = b.x * cos(a.end_angle) - b.y * sin(a.end_angle);
    double y = b.x * sin(a.end_angle) + b.y * cos(a.end_angle);
    return crane(x + a.x, y + a.y, a.end_angle + b.end_angle);
}

crane apply( crane a, int n ) {
    return crane(a.x, a.y, (n-180)*(PI/180));
}

int sizes[MAX];
crane gen( unsigned i ) {
    return crane(0, sizes[i-1], 0);
}
int N, C;

int main() {
    segment_tree< crane, int > tree;
    tree.merge = merge;
    tree.apply = apply;
    tree.identity = crane(0, 0, 0);
    const char * str = "";

    while( scanf("%d%d", &N, &C) != EOF ) {
        printf( "%s", str );
        str = "\n";
        for( int i = 0; i < N; ++i )
            scanf( "%d", &sizes[i] );
        tree.reset( N, gen );
        while( C-- ) {
            int n, a;
            scanf( "%d%d", &n, &a );
            tree.update( n, n, a );
            crane c = tree.query( 1, N );
            printf( "%.2lf %.2lf\n", c.x, c.y );
        }
    }
    return 0;
}

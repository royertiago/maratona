#include <stdio.h>
#include <math.h>
#include <float.h>

int max( int i, int j ) { return i > j ? i : j; }
template< typename T > T min( T i, T j ) { return i < j ? i : j; }

struct point {
    int x, y;
    point operator-( point p ) {
        point q;
        q.x = x - p.x;
        q.y = y - p.y;
        return q;
    }
    int operator*( point p ) {
        return x*p.y - y*p.x;
    }
};

int direction( point p, point a, point b ) {
    return (a - p) * (b - p);
}

bool on_line( point p, point a, point b ) {
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

bool intersect( point p, point q, point a, point b ) {
    int d1 = direction( p, q, a );
    int d2 = direction( p, q, b );
    int d3 = direction( a, b, p );
    int d4 = direction( a, b, q );
    if( ((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
        ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)) )
        return true;

    if( d1 == 0 && on_line( a, p, q ) ) return true;
    if( d2 == 0 && on_line( b, p, q ) ) return true;
    if( d3 == 0 && on_line( p, a, b ) ) return true;
    if( d4 == 0 && on_line( q, a, b ) ) return true;

    return false;
}

double distance( point p, point q ) {
    return sqrt( (p.x - q.x)*(p.x - q.x) +
                 (p.y - q.y)*(p.y - q.y) );
}

int main() {
    point S, T, A, B, C;
    double d[5][5];
    int n;
    scanf("%d", &n);
    while( n-- ) {
        scanf( "%d%d%d%d%d%d%d%d%d%d", &S.x, &S.y, &T.x, &T.y, &A.x, 
                                       &A.y, &B.x, &B.y, &C.x, &C.y );

        for( int i = 0; i < 5; ++i )
            for( int j = 0; j < 5; ++j )
                d[i][j] = DBL_MAX;
        for( int i = 0; i < 5; ++i )
            d[i][i] = 0;
        d[2][3] = d[3][2] = distance(A,B);
        d[3][4] = d[4][3] = distance(C,B);
        d[4][2] = d[2][4] = distance(C,A);
        if( !intersect(S, T, A, B) && !intersect(S, T, B, C) )
            d[0][1] = d[1][0] = distance(S, T);
        if( !intersect(S, C, A, B) )
            d[0][4] = d[4][0] = distance(S, C);
        if( !intersect(S, A, C, B) )
            d[0][2] = d[2][0] = distance(S, A);
        if( !intersect(T, C, A, B) )
            d[1][4] = d[4][1] = distance(T, C);
        if( !intersect(T, A, C, B) )
            d[1][2] = d[2][1] = distance(T, A);
        if( (direction(T, B, C) >= 0 && direction(T, B, A) >= 0)||
            (direction(T, B, C) <= 0 && direction(T, B, A) <= 0) )
            d[1][3] = d[3][1] = distance(T, B);
        if( (direction(S, B, C) >= 0 && direction(S, B, A) >= 0)||
            (direction(S, B, C) <= 0 && direction(S, B, A) <= 0) )
            d[0][3] = d[3][0] = distance(S, B);

        for( int k = 0; k < 5; ++k )
            for( int j = 0; j < 5; ++j )
                for( int i = 0; i < 5; ++i )
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        printf( "%.6lf\n", d[0][1] );
    }
    return 0;
}

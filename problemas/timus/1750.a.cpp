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
    int n;
    scanf("%d", &n);
    while( n-- ) {
        scanf( "%d%d%d%d%d%d%d%d%d%d", &S.x, &S.y, &T.x, &T.y, &A.x, 
                                       &A.y, &B.x, &B.y, &C.x, &C.y );

        if( !intersect(S, T, A, B) && !intersect(S, T, B, C) ) {
            //printf( "ST\n" );
            printf( "%.6lf\n", distance(S, T) );
        }
        else {
            double candidate = DBL_MAX;
            if( !intersect(S, A, B, C) ) { // Primeiro, nos deslocaremos para A.
                double current = distance(S, A);
                if( !intersect(A, T, B, C) ) {
                    //printf( "SAT\n" );
                    candidate = min(candidate, current + distance(A, T)); // S-A-T
                }
                else {
                    // Estamos em A, e não dá para ir direto a T por causa de BC.
                    //printf( "SACT\n" );
                    //printf( "SABT\n" );
                    candidate = min(candidate, current + distance(A, C) + distance(C, T)); //S-A-C-T
                    candidate = min(candidate, current + distance(A, B) + distance(B, T)); //S-A-B-T
                    // Note que o último caminho é válido, pois o segmento BC intersecta AT
                }   
            }
            if( !intersect(S, C, B, A) ) { // Agora, tentaremos ir por C.
                double current = distance(S, C);
                if( !intersect(C, T, B, A) ) {
                    //printf( "SCT\n" );
                    candidate = min(candidate, current + distance(C, T)); // S-C-T
                }
                else {
                    //printf( "SCAT\n" );
                    //printf( "SCBT\n" );
                    candidate = min(candidate, current + distance(C, A) + distance(A, T)); //S-C-A-T
                    candidate = min(candidate, current + distance(C, B) + distance(B, T)); //S-C-B-T
                }   
            }
            // Agora, vamos por B.
            double current = distance(S, B);
            if( !intersect(C, T, A, B) ) {
                //printf( "SBCT\n" );
                candidate = min(candidate, current + distance(B, C) + distance(C, T)); // S-B-C-T
            }
            if( !intersect(A, T, C, B) ) {
                //printf( "SBAT\n" );
                candidate = min(candidate, current + distance(B, A) + distance(A, T)); // S-B-A-T
            }
            /* Do ponto de vista de S, A e B devem estar em lados diferentes de B
             * para ter certeza de que não atravessaremos a ravina. */
            if( ((direction(T, B, C) >= 0 && direction(T, B, A) >= 0)||
                 (direction(T, B, C) <= 0 && direction(T, B, A) <= 0)) &&
                ((direction(S, B, C) >= 0 && direction(S, B, A) >= 0)||
                 (direction(S, B, C) <= 0 && direction(S, B, A) <= 0)) ) {
                candidate = min(candidate, current + distance(B, T) ); // S-B-T
                //printf( "SBT\n" );
            }

            // Finalmente,
            printf( "%.6lf\n", candidate );
        }
    }
    return 0;
}

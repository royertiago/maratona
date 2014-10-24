/* horrible.cpp
 * Problema: http://br.spoj.com/problems/HORRIBLE/
 *
 * Árvore de segmentos.
 */
#include <stdio.h>

#define MAX2 131072

typedef long long ll;

ll segments[2*MAX2];
ll lazy[2*MAX2];
int N, C;

int first_power( unsigned i ) {
    int d = 8u*sizeof(unsigned) - __builtin_clz(i) - 1;
    if( i == (1u << d) ) return i;
    return 1 << (d+1);
}

void reset() {
    for( int i = 0; i < 2*first_power(N); ++i )
        segments[i] = lazy[i] = 0;
}

void update( int min, int max, int smin, int smax, int index, ll v ) {
    segments[index] += v * (max - min + 1);
    int middle = smin + (smax - smin) / 2;
    if( min == smin && max == smax )
        lazy[index] += v;
    else if( max <= middle )
        update( min, max, smin, middle, 2*index, v );
    else if( min >= middle + 1 )
        update( min, max, middle + 1, smax, 2*index + 1, v );
    else {
        update( min, middle, smin, middle, 2*index, v );
        update( middle + 1, max, middle + 1, smax, 2*index + 1, v );
    }
}

ll query( int min, int max, int smin, int smax, int index ) {
    ll lazy_value = (max - min + 1) * lazy[index];
    int middle = smin + (smax - smin) / 2;
    if( min == smin && max == smax )
        return segments[index];
    if( max <= middle )
        return query(min, max, smin, middle, 2*index) + lazy_value;
    if( min >= middle + 1 )
        return query(min, max, middle + 1, smax, 2*index + 1) + lazy_value;

    return query( min, middle, smin, middle, 2*index) +
           query( middle + 1, max, middle + 1, smax, 2*index + 1) + lazy_value;
}

int main() {
    int cases;
    scanf( "%d", &cases );
    while( cases-- ) {
        scanf("%d%d", &N, &C);
        reset();
        while( C-- ) {
            int t, a, b, v;
            scanf( "%d", &t );
            if( t == 0 ) {
                scanf( "%d%d%d", &a, &b, &v );
                update( a, b, 1, N, 1, v );
            } else {
                scanf( "%d%d", &a, &b );
                printf( "%lld\n", query(a, b, 1, N, 1) );
            }
        }
    }
    return 0;
}

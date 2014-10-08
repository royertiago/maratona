#include <stdio.h>
#include <math.h>
#include <stdint.h>

#ifdef ONLINE_JUDGE
#define NDEBUG
#endif
#include <assert.h>

typedef long long unsigned llu;

// Retorna a * b mod m
llu mm( llu a, llu b, llu m ) {
    unsigned step = __builtin_clzll(m);
    llu mask = (1llu << step) - 1;
    a %= m; b %= m;
    llu res = 0;
    do {
        res = ( res + a * (b & mask) ) % m;
        a = (a << step) % m;
    } while( (b >>= step) != 0 );
    return res;
}

llu N, K, M;

void mult( llu a[2][2], llu b[2][2] ) {
    llu aux[2][2];
    for( int i = 0; i < 2; ++i )
    for( int j = 0; j < 2; ++j ) {
        aux[i][j] = 0;
        for( int k = 0; k < 2; ++k )
            aux[i][j] = (aux[i][j] + mm(a[i][k],b[k][j], M) ) % M;
    }

    for( int i = 0; i < 2; ++i )
    for( int j = 0; j < 2; ++j )
        a[i][j] = aux[i][j];
}

int main() {
    scanf( "%llu%llu%llu", &N, &K, &M );
    llu m[2][2] = {
        {K-1, K-1},
        {1, 0}
    };
    llu power[2][2] = {
        {1, 0},
        {0, 1}
    };
    llu v[2] = {
        1,
        0
    };
    while( N != 0 ) {
        if( N % 2 == 1 )
            mult(power, m);
        mult(m, m);
        N >>= 1;
    }

    printf( "%llu\n", (mm(power[0][0], v[0], M) + mm(power[0][1],v[1], M) ) % M );
    return 0;
}

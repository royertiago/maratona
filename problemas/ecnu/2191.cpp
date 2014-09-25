#include <stdio.h>
#include <algorithm>
#include <utility>

using namespace std;
typedef long long unsigned ll;
typedef pair<unsigned, ll> limit;
#define index first
#define value second
#define MOD 1000000007

limit limits[500*1000];
ll bit[500*1000 + 1];
unsigned A[100];
unsigned N, n, m;
ll X, Y, Z;

bool ordered( limit a, limit b ) {
    if( a.value < b.value ) return true;
    if( a.value > b.value ) return false;
    return a.index > b.index;
}

ll get( unsigned index ) {
    ll result = 0;
    while( index != 0 ) {
        result = (result + bit[index]) % MOD;
        index -= index & -index;
    }
    return result;
}

void set( unsigned index, ll increment ) {
    while( index <= n ) {
        bit[index] = (bit[index] + increment) % MOD;
        index += index & -index;
    }
}

ll solve() {
    for( ll i = 0; i <= n; ++i )
        bit[i] = 0;
    for( ll i = 0; i < n; ++i )
        set( limits[i].index, get(limits[i].index) + 1 );
    return get( n );
}

int main() {
    scanf( "%u", &N );
    for( int current = 1; current <= N; ++current ) {
        scanf( "%u%u%llu%llu%llu", &n, &m, &X, &Y, &Z );
        for( int i = 0; i < m; ++i )
            scanf( "%u", &A[i] );

        for( int i = 0; i < n; ++i ) {
            limits[i].value = A[i % m];
            limits[i].index = i + 1;
            A[i % m] = (X * A[i % m] + Y *(i + 1)) % Z;
        }
        
        sort( limits, limits + n, ordered );
        printf( "Case #%d: %llu\n", current, solve() );
    }
    return 0;
}

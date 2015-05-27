#include <stdio.h>
#define MOD (int)(1e9 + 7)

bool valid_delta( int i, int j ) {
    if( i < 0 )
        i = -i;
    if( j < 0 )
        j = -j;

    if( i == 1 || j == 1 )
        return true;
    if( i == 0 || j == 0 || i == j )
        return false;

    for( int k = 2; k < 5; k++ )
        if( i % k == 0 && j % k == 0 )
            return false;

    return true;
}

struct matrix {
    long long v[25][25];
};

void build( matrix& a, int size ) {
    for( int i = 0; i < size; i++ )
        for( int j = 0; j < size; j++ )
            for( int ki = 0; ki < size; ki++ )
                for( int kj = 0; kj < size; kj++ )
                    if( valid_delta( ki - i, kj - j ) )
                        a.v[i*size + j][ki*size + kj] = 1;
                    else
                        a.v[i*size + j][ki*size + kj] = 0;
}

// a = a * b
void mult( matrix& a, const matrix& b, int size ) {
    matrix m = {{0}};
    for( int i = 0; i < size; i++ )
        for( int j = 0; j < size; j++ )
            for( int k = 0; k < size; k++ )
                m.v[i][j] = (m.v[i][j] + a.v[i][k] * b.v[k][j]) % MOD;
    a = m;
}

long long solve( int size, long long count ) {
    matrix a = {{0}}, e = {{0}};
    
    build( a, size );
    for( int i = 0; i < size*size; i++ )
        e.v[i][i] = 1;

    while( count > 0 ) {
        if( count % 2 == 1 )
            mult( e, a, size*size );
        mult( a, a, size*size );
        count >>= 1;
    }

    long long sum = 0;
    for( int i = 0; i < size*size; i++ )
        for( int j = 0; j < size*size; j++ )
            sum += e.v[i][j];
    return sum % MOD;
}

int main() {
    int size;
    long long count;
    while( scanf("%d%lld", &size, &count ) != EOF )
        printf( "%lld\n", solve(size, count) );
    return 0;
}

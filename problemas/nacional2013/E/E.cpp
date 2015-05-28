#include <stdio.h>

typedef long long int lli;
#define MOD (lli)(1e9 + 7)

lli binom[100][100];
void binom_precalc() {
    for( int i = 0; i < 100; i++ ) {
        binom[i][0] = 1;
        binom[i][i] = 1;
    }
    for( int i = 1; i < 100; i++ )
        for( int j = 1; j < i; j++ )
            binom[i][j] = (binom[i-1][j] + binom[i-1][j-1]) % MOD;
}

char str[101];
int size;

// Resolve o problema, mas assume que pode por o zero na frente.
lli solve( const int * count, int target ) {
    lli a[11][51] = {1};
    int digit_count = 0;
    for( int d = 0; d <= 9; d++ ) {
        lli b[11][51] = {0};

        for( int r = 0; r <= count[d]; r++ ) { // odd [r]epetitions
            int delta = r * d - (count[d] - r) * d;
            delta = (delta % 11 + 11) % 11;

            for( int i = 0; i < 11; i++ ) {
                for( int j = 0; j + r <= (size + 1)/2; j++ ) {
                    int ni = (i + delta) % 11;
                    int nj = j + r;

                    int odd = j;
                    int even = digit_count - j;
                    if( even < 0 )
                        break;

                    int odd_plus = r;
                    int even_plus = count[d] - r;
                    b[ni][nj] = (b[ni][nj] +
                        a[i][j] * binom[odd + odd_plus][odd_plus] % MOD *
                        binom[even + even_plus][even]
                    ) % MOD;
                }
            }
        }

        digit_count += count[d];
        for( int i = 0; i < 11; i++ )
            for( int j = 0; j <= (size + 1)/2; j++ )
                a[i][j] = b[i][j];
    }
    return a[target][(size + 1)/2];
}

// Resolve o problema por completo.
lli solve() {
    int count[10] = {0};
    for( size = 0; str[size] != '\0'; size++ )
        count[str[size]-'0']++;

    size--;
    lli sum = 0;
    for( int i = 1; i <= 9; i++ ) {
        if( count[i] == 0 )
            continue;

        count[i]--;
        sum += solve(count, ((size + 1) % 2 == 0) ? i : 11 - i);
        count[i]++;
    }
    return sum % MOD;
}

int main() {
    binom_precalc();
    while( scanf("%s", str) != EOF )
        printf( "%lld\n", solve() );
    return 0;
}

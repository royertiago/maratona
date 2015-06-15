#include <stdio.h>

constexpr int mod = 1e3;

int pow_cache[mod];
int pow_mod;
int pow_shift;
void pow_precalc() {
    int reverse_pow[mod];
    for( int i = 0; i <= 1e3; i++ )
        reverse_pow[i] = -1;

    pow_cache[0] = 1;
    reverse_pow[0] = 0;

    for( int i = 1; i <= 1e3; i++ ) {
        pow_cache[i] = (pow_cache[i-1] * 2) % mod;
        if( reverse_pow[pow_cache[i]] == -1 )
            reverse_pow[pow_cache[i]] = i;
        else {
            pow_shift = reverse_pow[pow_cache[i]];
            pow_mod = i - pow_shift;
            break;
        }
    }
}

// Computa 2^i % mod
int pow( int i ) {
    return pow_cache[ (i-pow_shift) % pow_mod + pow_shift ];
}

struct K {
    int mod; // Produto de todos os primos não-múltiplos de 2 ou 5, módulo 1000
    int pow2; // Quantidade de potências de 2 no número

    int result() {
        return mod * pow(pow2) % 10;
    }
};

K cache[(int)1e6 + 1];
int last_cached;

int solve( int n ) {
    if( n <= last_cached )
        return cache[n].result();

    K k = cache[last_cached];
    for( int i = last_cached + 1; i <= n; i++ ) {
        int j = i;
        while( j % 2 == 0 ) {
            j /= 2;
            k.pow2++;
        }
        while( j % 5 == 0 ) {
            j /= 5;
            k.pow2--;
        }
        k.mod = (k.mod * j) % mod;
        cache[i] = k;
    }
    last_cached = n;
    return k.result();
}

int main() {
    pow_precalc();
    cache[0] = cache[1] = {1, 0};
    last_cached = 1;
    int k, i = 1;;
    while( scanf( "%d", &k ) != EOF )
        printf( "Instancia %d\n%d\n\n", i++, solve(k) );

    return 0;
}

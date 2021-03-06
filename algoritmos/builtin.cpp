/* builtin.cpp
 * Lista dos builtins do gcc, com implementações alternativas. 
 */
#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <assert.h>

/* int __builtin_ffs( int x )
 * Returna log2( x & -x ) + 1, isto é, 1 + índice do bit 1 menos significativo. */
int ffs( int x ) {
    if( x == 0 ) return 0;
    int v = 1;
    while( x % 2 == 0 ) {
        x >>= 1;
        v++;
    }
    return v;
}

/* int __builtin_ctz( int x )
 * Retorna a quantidade de zeros depois do bit 1 menos significativo.
 * O resultado é indefinido para x == 0.
 * Equivalente a ffs(x) - 1, se x != 0.
 */
int ctz( unsigned x ) {
    return ffs(x) - 1;
}

/* int __builtin_clz( int x )
 * Retorna a quantidade de zeros antes do bit 1 mais significativo.
 * O resultado é indefinido para x == 0.
 * log2(x) == sizeof(unsigned)*CHAR_BIT - 1 - clz(x). */
int clz( unsigned x ) {
    int v = (int) sizeof(unsigned)*CHAR_BIT - 1;
    while( (x >>= 1) != 0 )
        v--;
    return v;
}

/* int __builtin_popcount( unsigned x )
 * Retorna a quantidade de bits 1 na representação binária de x.
 */
int popcount( unsigned x ) {
    int v = 0;
    while( x != 0 ) {
        v++;
        x -= x & -x;
    }
    return v;
}

/* int __builtin_parity( unsigned x )
 * Returna __builtin_popcount(x) % 2. */
int parity( unsigned x ) {
    return popcount(x) % 2;
}

uint16_t swap16( uint16_t x ) {
    return x << 8u | x >> 8;
}
uint32_t swap32( uint32_t x ) {
    return x << 24 | (x & 0xFF00) << 8 | x >> 8 & 0xFF00 | x >> 24;
}
uint64_t swap64( uint64_t x ) {
    return x << 56 | (x & 0xFF00) << 40 | (x & 0xFF0000) << 24 | (x & 0xFF000000) << 8
           | x >> 8 & 0xFF000000 | x >> 24 & 0xFF0000 | x >> 40 & 0xFF00 | x >> 56;
}

int main() {
    for( int i = -65536; i < 65535; ++i )
        assert( __builtin_ffs(i) == ffs(i) );
    assert( __builtin_ffs(INT_MAX) == ffs(INT_MAX) );
    assert( __builtin_ffs(INT_MIN) == ffs(INT_MIN) );

    for( unsigned i = 1; i < 65535; ++i )
        assert( __builtin_ctz(i) == ctz(i) );
    assert( __builtin_ctz(UINT_MAX) == ctz(UINT_MAX) );
    assert( __builtin_ctz(INT_MAX) == ctz(INT_MAX) );
    assert( __builtin_ctz(INT_MAX+1u) == ctz(INT_MAX+1u) );

    for( unsigned i = 1; i < 65535; ++i )
        assert( __builtin_clz(i) == clz(i) );
    assert( __builtin_clz(UINT_MAX) == clz(UINT_MAX) );
    assert( __builtin_clz(INT_MAX) == clz(INT_MAX) );
    assert( __builtin_clz(INT_MAX+1u) == clz(INT_MAX+1u) );

    for( unsigned i = 1; i < 65535; ++i )
        assert( __builtin_popcount(i) == popcount(i) );
    assert( __builtin_popcount(UINT_MAX) == popcount(UINT_MAX) );
    assert( __builtin_popcount(INT_MAX) == popcount(INT_MAX) );
    assert( __builtin_popcount(INT_MAX+1u) == popcount(INT_MAX+1u) );

    for( unsigned i = 1; i < 65535; ++i )
        assert( __builtin_parity(i) == parity(i) );
    assert( __builtin_parity(UINT_MAX) == parity(UINT_MAX) );
    assert( __builtin_parity(INT_MAX) == parity(INT_MAX) );
    assert( __builtin_parity(INT_MAX+1u) == parity(INT_MAX+1u) );

    for( uint16_t i = 1; i < 65535; ++i )
        assert( __builtin_bswap16(i) == swap16(i) );

    for( uint32_t i = 1; i < 1u << 31; i += 12345 )
        assert( __builtin_bswap32(i) == swap32(i) );

    for( uint64_t i = 1; i < 1u << 31; i += 1234567 )
        assert( __builtin_bswap64(i) == swap64(i) );
    return 0;
}

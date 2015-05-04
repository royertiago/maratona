#include <stdio.h>

/* O problema fica trivial usando __builtin_popcount.
 * Entretanto, precisamos cuidar com memórias de tamanho 2^32.
 */

int main() {
    int N;
    while( scanf("%d", &N) != EOF && N != 0 ) {
        int sum = 0;
        while( N-- ) {
            long long unsigned pente;
            scanf( "%llu", &pente );
            sum += __builtin_popcount(pente);
        }
        printf( "%d\n", sum );
    }
    return 0;
}

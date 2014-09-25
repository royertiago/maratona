/* 2189.cpp
 * Problema: http://acm.cs.ecnu.edu.cn/problem.php?problemid=2189
 */
#include <stdio.h>
#include <algorithm>
int main() {
    int N, P, K, L;
    int freq[1000];
    scanf( "%d", &N );
    for( int NN = 1; NN <= N; NN++ ) {
        scanf( "%d %d %d", &P, &K, &L );
        for( int j = 0; j < L; ++j )
            scanf( "%d", &freq[j] );
        std::sort( freq, freq + L );
        std::reverse( freq, freq + L );
        long long unsigned total = 0;
        for( int k = 0; k < L; k++ )
            total += freq[k] * ((k + K)/K);

        printf( "Case #%d: %llu\n", NN, total );
    }

    return 0;
}

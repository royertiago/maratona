#include <stdio.h>

#define MAX 500
int areas[MAX][MAX];
int N, M;
int lower, upper;

/* Retorna o menor i tal que vec[i] >= lower,
 * ou M caso nenhum seja. */
int lower_bound( int * vec ) {
    int min = 0, max = M;
    while( min < max ) {
        int middle = min + (max-min)/2;
        if( vec[middle] >= lower )
            max = middle;
        else{
            min = middle + 1;
        }
    }
    return max;
}

/* Retorna o maior x tal que areas[i+x][j+x] <= upper,
 * ou -1 caso não exista. */
int binary_search( int i, int j ) {
    if( areas[i][j] > upper ) return -1;
    int min = 0;
    int max = N - i > M - j ? M - j : N - i;
    max--; // areas[i + (N-i)] == areas[N] não existe.
    while( min < max ) {
        int middle = min + (max - min + 1)/2;
        if( areas[i+middle][j+middle] <= upper )
            min = middle;
        else
            max = middle - 1;
    }
    return min;
}

int solve() {
    int best = 0;
    for( int i = 0; i < N; ++i ) {
        int j = lower_bound( areas[i] );
        if( j == M ) continue;
        int k = binary_search( i, j );
        best = best > k+1 ? best : k+1;
    }
    return best;
}

int main() {
    while( scanf("%d%d", &N, &M) != EOF && N != 0 ) {
        for( int i = 0; i < N; ++i )
            for( int j = 0; j < M; ++j )
                scanf( "%d", &areas[i][j] );
        int Q;
        scanf( "%d", &Q );
        while( Q-- ) {
            scanf( "%d%d", &lower, &upper );
            printf( "%d\n", solve() );
        }
        printf( "-\n" );
    }
    return 0;
}

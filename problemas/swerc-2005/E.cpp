#include <stdio.h>
#include <algorithm>

int a[4000], b[4000], c[4000], d[4000];
int sab[4000*4000], scd[4000*4000];
int n;

int solve() {
    int k = 0;
    for( int i = 0; i < n; i++ )
        for( int j = 0; j < n; j++ ) {
            sab[k] = a[i] + b[j];
            scd[k] = c[i] + d[j];
            k++;
        }

    std::sort( sab, sab + k );
    std::sort( scd, scd + k );

    int i = 0, j = k - 1;
    int count = 0;
    while( i < k && j >= 0 ) {
        if( sab[i] + scd[j] > 0 )
            j--;
        else if( sab[i] + scd[j] < 0 )
            i++;
        else {
            /* Found a value whose sum is zero!
             * Let's count every possible secondary solution.
             */
            int ci = 0, cj = 0;
            do {
                i++;
                ci++;
            } while( i < k && sab[i] == sab[i - 1] );
            do {
                j--;
                cj++;
            } while( j >= 0 && scd[j] == scd[j + 1] );
            count += ci * cj;
        }
    }
    return count;
}

int main() {
    while( scanf("%d", &n) != EOF && n != 0 ) {
        for( int i = 0; i < n; i++ )
            scanf( "%d%d%d%d", &a[i], &b[i], &c[i], &d[i] );
        printf( "%d\n", solve() );
    }
    return 0;
}

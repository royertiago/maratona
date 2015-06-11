/* Problem: http://www.codechef.com/problems/CKISSHUG
 *
 * The catch of the problem is that,
 * after the princess kisses the first guess,
 * around half of the remaining guests must also be kissed;
 * but the princess' greeting remains unrestrained to the other half.
 *
 * To generate all possible greeting sequences,
 * make a decision tree.
 * Suppose there are N guests.
 * The first thing the princess must decide is the first guest to kiss,
 * or not to kiss at all.
 *
 * Suppose she kisses the guest n first;
 * there are N-n remaining guests to be greeted.
 * Exactly ceil((N-n)/2) of them are now "locked":
 * due to princess' compulsion, she will kiss all these guests.
 * The other floor((N-n)/2) == (N-n+1)/2 guests
 * are pretty much unrestrained; the princess may do anything.
 * So, there are exactly 2^((N-n+1)/2) possible greeting sequences
 * under this choice of n.
 *
 * Since any two choices that differ in n will be different,
 * every leaf in the decision branch is unique.
 * The solution is, therefore,
 *  S == 1 + \sum_{n = 1}^{N+1} 2^{\lfloor (N-n+1)/2 \rfloor}.
 *
 * Some algebra brings us to
 *  S == \sum_{n = 1}^{N+1} 2^{\lfloor (n-1)/2 \rfloor};
 * due to the floorings, there are two sums of consecutive powers of two
 * that goes up to something about N/2.
 * A more careful analysis,
 * together with the formula
 *  \sum_{k=0}^N 2^k == 2^{k+1} - 1,
 * gives the nice equation
 *  S == 2^{(N+1)/2} + 2^{(N+2)/2} - 2.
 */
#include <stdio.h>

#define MOD (long long)(1e9 + 7)

// Computes 2^i mod MOD.
int pow( int i ) {
    long long r = 1;
    long long e = 2;
    while( i != 0 ) {
        if( i % 2 == 1 )
            r = (r * e) % MOD;
        i >>= 1;
        e = (e * e) % MOD;
    }
    return r;
}

int solve( int N ) {
    return (long long)(pow( (N+1)/2 ) + pow( (N+2)/2 ) + MOD - 2 ) % MOD;
}

int main() {
    int t;
    scanf( "%d", &t );
    while( t-- ) {
        int i;
        scanf( "%d", &i );
        printf( "%d\n", solve(i) );
    }
    return 0;
}

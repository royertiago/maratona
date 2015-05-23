/* Problema C da etapa regional da Maratona de 2009.
 *
 * Ad-hoc vector indexing and traversal problem.
 *
 * We will call a the first vector and b the second; n and m are their sizes.
 * The first step is to remove every duplicate entry,
 * via std::unique. Also, reassign the vector sizes.
 *
 * Create two indexes, i and j, for a and b, respectively.
 * The idea is to iterate through both vectors simultaneously,
 * always trying to keep a[i] and b[j] as "equal" as possible.
 * We will increment two counters, ca and cb, with the number
 * of cards that appear in a but not in b, and vice-versa, respectively.
 *
 * We will call the set of elements a[i-1], a[i-2], ...,
 * and b[j-1], b[j-2], ... (when these indexes make sense)
 * the "analyzed values".
 * We mark a value as analyzed by incrementing its respective index.
 *
 * We will impose a loop invariant: the minimum between a[i] and b[j]
 * will be strictly greater than any analyzed value.
 * Note that, with i = j = 0 at the beginning, this invariant is true.
 * We will make use of this invariant and the input ordering guarantee
 * to prove an element is unique in time O(1).
 *
 * We have three possibilities between a[i] and b[j].
 * - a[i] < b[j].
 *   Then, the minimum is a[i].
 *   Every other unanalyzed element in a is greater than a[i],
 *   and every unanalyzed element in b is greater than a[i]
 *   (both results come from the fact that a and b are ordered and free of duplicates).
 *   Thus, a[i] is unique in a.
 *   Increment ca, and advance i;
 *   the invariant is kept because we just analyzed a[i],
 *   and the next minimum element is greater than a[i],
 *   which is greater than or equal to every analyzed element.
 * - a[i] > b[j].
 *   Same reasoning; increment cb and advance j.
 * - a[i] == b[j].
 *   Advance both i and j.
 *   This will keep the invariant,
 *   because every element in a and b after i and j (respectively)
 *   are greater than a[i] (or b[j]).
 *
 * Stop condition: the ideal "last movement" is when a[i] == b[j].
 * We advance both i and j, both indexes become out of bounds simultaneously.
 * The easiest way of doing this is to add a sentinel value,
 * greater than any existing card in a and b,
 * to the end of both arrays.
 * The minimum between any card and the sentinel is the other card,
 * so we will only mark the sentinel as analyzed when analyzing both sentinels.
 * Since the sentinel values are equal,
 * this can only happen at the a[i] == b[j] situation above.
 * Thus, we keep iterating until either i or j become greater than n or m,
 * respectively.
 * In fact, as both indexes will become out of bounds simultaneously,
 * we may just check for one of them
 * (as is done below).
 */
#include <stdio.h>
#include <algorithm>

// One extra element for the sentinel
int a[(int)1e4 + 1], b[(int)1e4 + 1];
int n, m;

int solve() {
    a[n++] = b[m++] = 1e7; // sentinel value
    n = std::unique( a, a+n ) - a;
    m = std::unique( b, b+m ) - b;

    int i = 0, j = 0;
    int ca = 0, cb = 0;
    while( i != n ) {
        if( a[i] < b[j] ) {
            ca++;
            i++;
        }
        else if( a[i] > b[j] ) {
            cb++;
            j++;
        }
        else {
            i++;
            j++;
        }
    }

    return ca < cb ? ca : cb;
}

int main() {
    while( scanf("%d %d", &n, &m) != EOF && n != 0 ) {
        for( int i = 0; i < n; i++ )
            scanf( "%d", &a[i] );
        for( int i = 0; i < m; i++ )
            scanf( "%d", &b[i] );
        printf( "%d\n", solve() );
    }
    return 0;
}

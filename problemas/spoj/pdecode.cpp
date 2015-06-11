/* Problem: http://www.spoj.com/problems/PDECODE/
 * Modular exponentiation with permutations.
 *
 * To simplify applying the permutation,
 * we will index arrays by 1, not by zero;
 * so, our arrays will be 1 unit larger than usual.
 */
#include <stdio.h>

char base_str[83];
char base_solution[83];
char * const str = base_str + 1;
char * const solution = base_solution + 1;
/* We need 3 extra chars:
 *  - one for the '\0'
 *  - one to cope with the 1-indexing,
 *  - and one for the '\n' that fgets appends.
 */

int perm[81]; // Permutation given by the problem
int inv[81]; // Inverse of perm

int n, m;

/* a = a * b
 * That is, compose the permutations a and b
 * and put the result in a.
 */
void compose( int * a, int * b ) {
    int c[81];
    for( int i = 1; i <= n; i++ )
        c[i] = b[a[i]];
    for( int i = 1; i <= n; i++ )
        a[i] = c[i];
}

void solve() {
    for( int i = 1; i <= n; i++ )
        inv[perm[i]] = i;

    int base[81];
    for( int i = 1; i <= n; i++ )
        base[i] = i;
    /* We will repeatedly square inv
     * and put the intermediade results in base.
     */

    while( m != 0 ) {
        if( m % 2 == 1 )
            compose( base, inv );
        compose( inv, inv );
        m >>= 1;
    }

    for( int i = 1; i <= n; i++ )
        base_solution[i] = base_str[base[i]];
    base_solution[n+1] = '\0';
}

int main() {
    while( scanf( "%d%d", &n, &m ) != EOF && n != 0 ) {
        for( int i = 1; i <= n; i++ )
            scanf( "%d", &perm[i] );

        fgets( str, 2, stdin ); // This removes the trailing '\n'
        fgets( str, 82, stdin ); // This actually scans the string.

        solve();

        /* Altough 'str' will contain the trailing '\n',
         * we do not copy it to 'solution', so we need to print it here.
         */
        printf( "%s\n", solution );
    }
    return 0;
}

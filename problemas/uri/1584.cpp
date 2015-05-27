/* Problema: https://www.urionlinejudge.com.br/judge/pt/problems/view/1584
 *
 * Modular exponentiation with matrices.
 *
 * The idea is to transform this problem in a linear algebra-based one.
 * Linearize the grid to a vector.
 * Fixed a size n, we will construct a sequence of vectors V_k,
 * such that the (n*i + j)-th element of the vector V_k
 * represents the number of possible unlock patterns with exactly K elements
 * ending in the node (i, j) of the grid.
 * (The number n*i+j has nothing special; it exists
 * only to name a mapping between the grid and the vector entries.)
 *
 * To construct V_{k+1} from V_k,
 * for a given entry n+i + j,
 * we just need to compute the sum of all nodes that can reach (i, j).
 * The key observation is that this is a fixed linear combination
 * of the entries of the vector V_k.
 * More specifically, V_{k+1,l} is the sum of all V_k_t
 * such that the node of the index t can reach the node of the index k.
 *
 * Therefore, there exist a square matrix A_n, of dimensions n^2
 * (thus n^4 entries) such than A_n^k * V_0 = V_k.
 * V_0 is a vector with all ones;
 * thus, the sum of the elements in V_k is the sum of the elements in A_n^k.
 * This matrix can be computed in O(ln k) matricial multiplications,
 * via modular exponentiation.
 * The function solve() takes care of this.
 *
 * It only remains to build such matrix A_n.
 * Note that
 * V_{k+1, l} = sum_{t is reachable from l} V_{k, t};
 * so, A_n will contain only ones or zeroes.
 * More specifically, A_{n, l, t} will be 1
 * if and only if the index l is reachable from the index t.
 * The function build iterates through all possible pairs (i,j)
 * and pairs (a,b), computes l and t, respectively,
 * and uses the function valid_delta to query wether l reaches t.
 *
 * Note that this problem is equivalent to the task of counting
 * the number of walks of size K through the graph of the grid.
 */
#include <stdio.h>
#define MOD (int)(1e9 + 7)

// Is (i, j) reachable from (0, 0)?
bool valid_delta( int i, int j ) {
    if( i < 0 )
        i = -i;
    if( j < 0 )
        j = -j;

    if( i == 1 || j == 1 )
        return true;
    if( i == 0 || j == 0 || i == j )
        return false;

    for( int k = 2; k < 5; k++ )
        if( i % k == 0 && j % k == 0 )
            return false;

    return true;
}

struct matrix {
    long long v[25][25];
};

// Constructs the matrix A_size.
void build( matrix& a, int size ) {
    for( int i = 0; i < size; i++ )
        for( int j = 0; j < size; j++ )
            for( int ki = 0; ki < size; ki++ )
                for( int kj = 0; kj < size; kj++ )
                    if( valid_delta( ki - i, kj - j ) )
                        a.v[i*size + j][ki*size + kj] = 1;
                    else
                        a.v[i*size + j][ki*size + kj] = 0;
}

// a = a * b
void mult( matrix& a, const matrix& b, int size ) {
    matrix m = {{0}};
    for( int i = 0; i < size; i++ )
        for( int j = 0; j < size; j++ )
            for( int k = 0; k < size; k++ )
                m.v[i][j] = (m.v[i][j] + a.v[i][k] * b.v[k][j]) % MOD;
    a = m;
}

long long solve( int size, long long count ) {
    matrix a = {{0}}, e = {{0}};
    
    build( a, size );
    for( int i = 0; i < size*size; i++ )
        e.v[i][i] = 1;

    while( count > 0 ) {
        if( count % 2 == 1 )
            mult( e, a, size*size );
        mult( a, a, size*size );
        count >>= 1;
    }

    long long sum = 0;
    for( int i = 0; i < size*size; i++ )
        for( int j = 0; j < size*size; j++ )
            sum += e.v[i][j];
    return sum % MOD;
}

int main() {
    int size;
    long long count;
    while( scanf("%d%lld", &size, &count ) != EOF )
        printf( "%lld\n", solve(size, count) );
    return 0;
}

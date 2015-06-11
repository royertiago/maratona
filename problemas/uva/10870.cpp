// Modular exponentiation.
#include <stdio.h>

struct matrix {
    int m[15][15];
};
int d, n, m;

// a = a * b
void mult( matrix & a, const matrix & b ) {
    matrix mat = {0};

    for( int i = 0; i < d; i++ )
    for( int j = 0; j < d; j++ )
    for( int k = 0; k < d; k++ )
        mat.m[i][j] = (mat.m[i][j] + a.m[i][k]*b.m[k][j]) % m;

    a = mat;
}

// mat = mat^n
void pow( matrix & mat ) {
    matrix r = {0};
    for( int i = 0; i < d; i++ )
        r.m[i][i] = 1;

    while( n != 0 ) {
        if( n % 2 == 1 )
            mult( r, mat );

        mult( mat, mat );
        n >>= 1;
    }
    mat = r;
}

int main() {
    while( scanf( "%d%d%d", &d, &n, &m ) != EOF && d != 0 ) {
        matrix base;
        matrix vec = {0};
        /* vec will contain the input values in descending order;
         * that is, vec[0][0] == a_n, vec[1][0] == a_{n-1},
         * and so on.
         * base will be built so that
         * base^n * vec == {a_{d+i}, a_{d+i-1}, ...};
         * then, by exponentiating base and multiplying vector,
         * the last value will be the answer.
         *
         * I am using a whole matrix to hold the vector
         * just to avoid implementing vector multiplication.
         * Is just a single multiplication anyway...
         */

        for( int i = 0; i < d; i++ )
        for( int j = 0; j < d; j++ )
            base.m[i][j] = 0;
        for( int i = 0; i < d-1; i++ )
            base.m[i+1][i] = 1;
        for( int i = 0; i < d; i++ ) {
            scanf( "%d", &base.m[0][i] );
            base.m[0][i] %= m;
        }
        for( int i = 0; i < d; i++ ) {
            scanf( "%d", &vec.m[d-i-1][0] );
            vec.m[d-i-1][0] %= m;
        }

        n--;
        /* This decrement is important.
         * If vec == {a_d, a_{d-1}, ..., a_1},
         * then
         * base^n * vec == {a_{d+n}, a_{d+n-1}, ..., a_{n+1}}.
         * Note we miss the value a_n, which is what we want;
         * the simplest solution is to decrement n before continuing.
         */

        if( n < d ) {
            /* UVa test cases actually do not check this.
             * (Or do not check properly.)
             * I've submitted a version with wrong indexing and it was accepted.
             */
            printf( "%d\n", vec.m[d-n-1][0] );
        }
        else {
            pow( base );
            mult( base, vec );
            printf( "%d\n", base.m[d-1][0] );
        }
    }
    return 0;
}

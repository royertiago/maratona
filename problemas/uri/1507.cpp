/* 1507.cpp
 * Problema: https://www.urionlinejudge.com.br/judge/en/problems/view/1507
 */

#include <stdio.h>

bool isSubseq( const char * seq, const char * subseq ) {
    --seq;
    while( *++seq != 0 )
        if( *seq == *subseq )
            ++subseq;
    return *subseq == 0;
}

int main() {
    char seq[100002], subseq[100002];
    // Precisamos de dois caracteres a mais: o '\0', e o '\n' que fgets insere.
    int cases, queries;
    scanf( "%d\n", &cases );
    while( cases-- ) {
        fgets( seq, sizeof(seq), stdin );
        scanf( "%d\n", &queries );
        while( queries-- ) {
            fgets( subseq, sizeof(subseq), stdin );
            printf( isSubseq(seq, subseq) ? "Yes\n" : "No\n" );
        }
    }
    return 0;
}

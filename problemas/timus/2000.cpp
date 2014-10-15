/* 2000.cpp
 * Problema: http://acm.timus.ru/problem.aspx?space=1&num=2000
 */
#include <stdio.h>
int vec[100*1000];
int n, p1, p2, pp1, pp2;

int sum_before( int i ) {
    int sum = 0;
    for( int j = 0; j < i; ++j )
        sum += vec[j];
    return sum;
}

int sum_after( int i ) {
    int sum = 0;
    for( int j = i + 1; j < n; ++j )
        sum += vec[j];
    return sum;
}

void simulate() {
    while( p1 <= p2 ) {
        pp1 += vec[p1];
        vec[p1++] = 0;
        pp2 += vec[p2];
        vec[p2--] = 0;
    }
    while( p2 <= p1 ) {
        pp1 += vec[p1];
        vec[p1--] = 0;
        pp2 += vec[p2];
        vec[p2++] = 0;
    }
}

int main() {
    scanf( "%d", &n );
    for( int i = 0; i < n; ++i )
        scanf( "%d", &vec[i] );
    scanf( "%d%d", &p1, &p2 );

    p1--; p2--;
    if( p1 < p2 ) {
        pp1 = sum_before( p1 );
        pp2 = sum_after( p2 );
        simulate();
    } else if( p2 < p1 ) {
        pp1 = sum_after( p1 );
        pp2 = sum_before( p2 );
        simulate();
    } else {
        pp1 = sum_before( p1 );
        pp2 = sum_after( p2 );
        if( pp2 > pp1 ) {
            int tmp = pp1;
            pp1 = pp2;
            pp2 = tmp;
        }
        pp1 += vec[p1];
    }

    printf( "%d %d\n", pp1, pp2 );

    return 0;
}

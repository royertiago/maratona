/* 1039.cpp
 * Problema: https://www.urionlinejudge.com.br/judge/en/problems/view/1039
 */
#include <stdio.h>
#include <math.h>

#define sqr(x) (x)*(x)

int main() {
    int r1, x1, y1, r2, x2, y2;
    while( scanf( "%d%d%d%d%d%d", &r1, &x1, &y1, &r2, &x2, &y2 ) == 6 ) {
        printf( sqrt( (double)sqr(x1-x2) + sqr(y1-y2) ) + r2 <= r1 ? "RICO\n" : "MORTO\n" );
    }
    return 0;
}

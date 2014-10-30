/* 1470.cpp
 * Problema: http://acm.timus.ru/problem.aspx?num=1470
 *
 * Árvore de Fenwick tridimensional.
 */
#include <stdio.h>

#define MAX 129
typedef long long ll;
ll ufos[MAX][MAX][MAX];
unsigned m;

void update( int x, int y, int z, ll v ) {
    x++; y++; z++;
    for( unsigned xi = x; xi <= m; xi += xi & -xi )
    for( unsigned yi = y; yi <= m; yi += yi & -yi )
    for( unsigned zi = z; zi <= m; zi += zi & -zi )
        ufos[xi][yi][zi] += v;
}

ll query( int x, int y, int z ) {
    ll sum = 0;
    for( unsigned xi = x; xi > 0; xi -= xi & -xi )
    for( unsigned yi = y; yi > 0; yi -= yi & -yi )
    for( unsigned zi = z; zi > 0; zi -= zi & -zi )
        sum += ufos[xi][yi][zi];
    return sum;
}

/* Por exemplo, em duas dimensões:
 *  a   .............
 *      .           .
 *      .           .
 *      .           .
 *      .           .
 *      .           .
 *  b   .............
 *      c           d
 *
 * A query ad retorna todas as células que estão à esquerda/abaixo da
 * célula ad, inclusive as que estão abaixo do quadrado especificado.
 * Então retiramos o resultado da busca bd e ac. Entretanto, as células
 * abaixo/esquerda de bc são removidas duas vezes, então temos de pô-las
 * de novo. */
ll query( int xmin, int xmax, int ymin, int ymax, int zmin, int zmax ) {
    xmax++; ymax++; zmax++;
    return query(xmax, ymax, zmax)
         - query(xmin, ymax, zmax)
         - query(xmax, ymin, zmax)
         + query(xmin, ymin, zmax)
         - query(xmax, ymax, zmin)
         + query(xmin, ymax, zmin)
         + query(xmax, ymin, zmin)
         - query(xmin, ymin, zmin);
}

int main() {
    scanf( "%u", &m );
    int t, xmin, xmax, ymin, ymax, zmin, zmax;
    ll v;
    while( scanf("%d", &t) != EOF && t != 3 )
        if( t == 2 ) {
            scanf( "%d%d%d%d%d%d", &xmin, &ymin, &zmin, &xmax, &ymax, &zmax );
            printf( "%lld\n", query(xmin, xmax, ymin, ymax, zmin, zmax) );
        } else {
            scanf( "%d%d%d%lld", &xmin, &ymin, &zmin, &v );
            update( xmin, ymin, zmin, v );
        }
    return 0;
}

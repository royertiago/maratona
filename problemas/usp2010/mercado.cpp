/* mercado.cpp
 * Problema D da maratona dos alunos da USP de 2010.
 * Mirror: http://br.spoj.com/problems/MCAIRO/
 *
 * Similar a gcj2008/1C.C, mas com duas dimensões.
 *
 * Defina pd[i][j] como sendo a maior quantidade de itens
 * compráveis navegando pelo mercado até o vendedor ij.
 * Ao adicionar um novo vendedor, precisamos atualizar a posição ij.
 * Pegue o máximo elemento do quadrado [1, i] x [1, j]; a nova rota
 * ideal para o elemento ij é seguir até este máximo e comprar mais
 * um item, com o vendedor ij. Ou seja: 
 *  pd[i][j] = 1 + max pd[x][y], x in [1, i], y in [1, j].
 * Podemos usar árvores de Fenwick para computar estes máximos; este
 * tipo de árvore computa, eficientemente, f(v[1], v[2], ..., v[k])
 * caso f seja associativa, e permite atualizar v[k] caso a operação
 * de atualização comute com f. Escolha f == std::max; atualizar
 * é calcular f(v[k], t) para algum t novo.
 */
#include <stdio.h>
#include <string.h>
#include <algorithm>

#define MAX 1000

int pd[MAX+1][MAX+1];

void update( int x, int y, int v ) {
    for( unsigned i = x; i <= MAX; i += i & -i )
    for( unsigned j = y; j <= MAX; j += j & -j )
        pd[i][j] = std::max( pd[i][j], v );
}

int retrieve( int x, int y ) {
    int v = 0;
    for( unsigned i = x; i != 0; i -= i & -i )
    for( unsigned j = y; j != 0; j -= j & -j )
        v = std::max( pd[i][j], v );
    return v;
}

int main() {
    int C, N, x, y;
    scanf( "%d", &C );
    while( C-- ) {
        scanf( "%d", &N );
        memset( pd, 0, sizeof pd );
        while( N-- ) {
            scanf( "%d%d", &x, &y );
            update( x, y, retrieve(x, y) + 1 );
        }
        printf( "%d\n", retrieve(MAX, MAX) );
    }
}

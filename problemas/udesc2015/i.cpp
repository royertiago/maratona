/* Problema B da seletiva doméstica da UDESC de 2015.
 *
 * Busca em largura (ou em profundidade). Complexidade: m*n.
 */
#include <stdio.h>
#include <queue>

struct pair { int x; int y; };

#define NORMAL '1'
#define ALAGADO '0'
#define VISITADO '*'

char status[1000][1001];

int n, m;

bool solve() {
    pair p; // Primeiro lugar não-alagado
    for( int i = 0; i < n; i++ )
        for( int j = 0; j < m; j++ )
            if( status[i][j] == NORMAL ) {
                p = pair{i, j};
                status[i][j] = VISITADO;
                goto found;
            }
    /* Caso extremo: todos os lugares estão alagados.
     */
    return true;
found:
    std::queue<pair> queue;
    queue.push(p);
    while( !queue.empty() ) {
        p = queue.front();
        queue.pop();

        if( p.x > 0 && status[p.x-1][p.y] == NORMAL ) {
            status[p.x-1][p.y] = VISITADO;
            queue.push( pair{p.x-1, p.y} );
        }
        if( p.y > 0 && status[p.x][p.y-1] == NORMAL ) {
            status[p.x][p.y-1] = VISITADO;
            queue.push( pair{p.x, p.y-1} );
        }
        if( p.x < n-1 && status[p.x+1][p.y] == NORMAL ) {
            status[p.x+1][p.y] = VISITADO;
            queue.push( pair{p.x+1, p.y} );
        }
        if( p.y < m-1 && status[p.x][p.y+1] == NORMAL ) {
            status[p.x][p.y+1] = VISITADO;
            queue.push( pair{p.x, p.y+1} );
        }
    }
    for( int i = 0; i < n; i++ )
        for( int j = 0; j < m; j++ )
            if( status[i][j] == NORMAL )
                return false;
    return true;
}

int main() {
    while( scanf( "%d %d", &n, &m ) == 2 && n != 0 && m != 0 ) {
        for( int i = 0; i < n; i++ )
            scanf( "%s", &status[i][0] );
        if( solve() )
            printf( "normal\n" );
        else
            printf( "isolados\n" );
    }
}

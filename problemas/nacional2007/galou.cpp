/* galou.cpp
 * Problema G da etapa nacional da Maratona de 2007.
 *
 * Busca em largura.
 */
#include <stdio.h>
#include <queue>

#define SIZE 100

struct coordinate {
    int x, y;
};

/* Possíveis deslocamentos no grafo. */
coordinate offset[] = {
    {0, -1},
    {1, -1},
    {1, 0},
    {0, 1},
    {-1, 1},
    {-1, 0}
};

char grid[SIZE][SIZE+1];
int R, C;

/* Simulação de sentinelas; caso i ou j estejam fora do grafo,
 * retorna apenas '.', que sabe-se que não será processado. */
inline char g( int i, int j ) {
    if( i < 0 || i >= R || j < 0 || j >= C )
        return '.';
    return grid[i][j];
}

char propagation( char c ) {
    if( c == ')' ) return '(';
    if( c == '(' ) return ')';
    return 'B';
}

void solve() {
    std::queue<coordinate> queue;
    // Busca linear para empilhar todos os 'I'
    for( int i = 0; i < R; ++i )
        for( int j = 0; j < C; ++j )
            if( grid[i][j] == 'I' ) {
                grid[i][j] = '(';
                queue.push({ i, j });
            }

    // Busca em largura padrão.
    while( !queue.empty() ) {
        coordinate c = queue.front();
        queue.pop();
        char p = propagation( grid[c.x][c.y] );
        for( auto o : offset ) {
            if( g(c.x + o.x, c.y + o.y) == '.' ) continue;
            if( g(c.x + o.x, c.y + o.y) == p ) continue;
            if( g(c.x + o.x, c.y + o.y) == '*' ) {
                /* Se achamos uma livre, propagamos p e
                 * enfileiramos a coordenada. */
                grid[c.x + o.x][c.y + o.y] = p;
                queue.push(coordinate{c.x + o.x, c.y + o.y});
            } else {
                /* Se não está nem livre nem é igual a p,
                 * então há um conflito. Empilhamos a coordenada
                 * pois ela precisa propagar o 'B'.*/
                grid[c.x + o.x][c.y + o.y] = 'B';
                queue.push(coordinate{c.x + o.x, c.y + o.y});
            }
        }
    }
    for( int i = 0; i < R; ++i )
        for( int j = 0; j < C; ++j )
            if( grid[i][j] == '*' )
                grid[i][j] = 'F';
}

int main() {
    while( scanf("%d%d", &R, &C) && R != 0 ) {
        for( int i = 0; i < R; ++i )
            scanf( "%s", grid[i] );
        solve();
        printf( "\n" );
        for( int i = 0; i < R; ++i )
            printf( "%s\n", grid[i] );
    }
    return 0;
}

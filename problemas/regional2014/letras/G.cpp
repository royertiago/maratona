/* G.cpp
 * Problema da etapa regional da maratona de 2014.
 */
#include <stdio.h>
#include <queue>
#include <utility>
#include <vector>

struct pair {
    unsigned x, y;
};

#define MAX 100

unsigned N;
unsigned p[MAX][MAX];
char q[MAX][MAX+1];

std::vector<pair> moves( pair pos ) {
    std::vector<pair> moves;
    if( pos.x > 0 ) moves.push_back({pos.x - 1, pos.y});
    if( pos.y > 0 ) moves.push_back({pos.x, pos.y - 1});
    if( pos.x < N - 1 ) moves.push_back({pos.x + 1, pos.y});
    if( pos.y < N - 1 ) moves.push_back({pos.x, pos.y + 1});
    return moves;
}

int solve() {
    if( p[0][0] != 0 || p[N-1][N-1] != 0 ) return MAX * MAX;

    std::queue<pair> queue;
        queue.push({0, 0});
    p[0][0]++;

    while( !queue.empty() ) {
        auto pos = queue.front();
        queue.pop();
        int next_value = p[pos.x][pos.y] + 1;
        for( auto next : moves(pos) )
            if( p[next.x][next.y] == 0 ) {
                queue.push(next);
                p[next.x][next.y] = next_value;
            }
    }
    if( p[N-1][N-1] == 0 ) return -1;
    return p[N-1][N-1];
}

void prepare( unsigned mask ) {
    for( unsigned i = 0; i < N; ++i )
    for( unsigned j = 0; j < N; ++j )
        if(q[i][j] >= 'A' && q[i][j] <= 'Z') {
            if( mask >> (q[i][j] - 'A') & 1u )
                p[i][j] = 0;
            else
                p[i][j] = MAX * MAX;
        } else {
            if( mask >> (q[i][j] - 'a') & 1u )
                p[i][j] = MAX * MAX;
            else
                p[i][j] = 0;
        }
}

int main() {
    scanf( "%u\n", &N );
    for( unsigned i = 0; i < N; ++i )
        scanf( "%s\n", &q[i][0] );

    unsigned best = MAX * MAX;
    for( unsigned i = 0; i <= 1024; ++i ) {
        prepare(i);
        unsigned sol = solve();
        if( sol != 0 && best > sol )
            best = sol;
    }
    if( best == MAX * MAX )
        printf( "-1\n" );
    else
        printf( "%d\n", best );

    return 0;
}

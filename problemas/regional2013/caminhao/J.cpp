/* J.cpp
 * Problema da etapa regional da maratona de 2013.
 *
 * Versão alternativa: https://www.urionlinejudge.com.br/judge/problems/view/1476
 */
#include <stdio.h>
#include <list>
#include <queue>
#include <vector>

#define MAX 20001
#define LOG2_MAX 15

int min( int i, int j ) { return i < j ? i : j; }
int max( int i, int j ) { return i > j ? i : j; }

struct bridge {
    int cost;
    int a, b;

    bool operator<( bridge rhs ) const {
        return cost < rhs.cost;
    }
};

struct ancestor_entry {
    int ancestor;
    int cost;
} ancestor[MAX][LOG2_MAX];

/* ancestor[i][j] aponta para um nodo que esteja
 * à distância 2**j de i. */

int C, P, Q; // Cidades, Pontes, Queries

std::list<bridge> city[MAX];
bool visited[MAX];
int depth[MAX];

void minimum_spanning_tree() {
    for( int i = 1; i <= C; ++i )
        visited[i] = false;
    ancestor[1][0] = {0, 0};

    std::priority_queue<bridge> queue;
    for( auto b : city[1] )
        queue.push( b );
    visited[1] = true;
    city[1].clear();

    while( !queue.empty() ) {
        bridge b = queue.top();
        queue.pop();
        if( visited[b.b] ) continue;

        visited[b.b] = true;
        ancestor[b.b][0] = ancestor_entry{b.a, b.cost};
        depth[b.b] = depth[b.a] + 1;

        for( auto c : city[b.b] )
            queue.push( c );
    }
}

void least_common_ancestor_init() {
    for( int k = 0; k < 15; ++k )
        ancestor[0][k] = {0, 0};

    for( int i = 1; i <= 31 - __builtin_clz((unsigned) C); ++i )
    for( int j = 1; j <= C; ++j ) {
        ancestor[j][i].ancestor = ancestor[ancestor[j][i-1].ancestor][i-1].ancestor;
        ancestor[j][i].cost = min( ancestor[j][i-1].cost,
                                   ancestor[ancestor[j][i-1].ancestor][i-1].cost );
        /* O menor custo entre ir até a metade (ancestor[j][i-1], chamaremos de k)
         * e ir da metade até o fim (ancestor[k][i-1]). */
    }
}

int solve( int u, int v ) {
    if( depth[u] < depth[v] ) return solve(v, u);
    int cost = 10000000;

    while( depth[u] > depth[v] ) {
        int index = __builtin_ffs( depth[u] - depth[v] ) - 1;
        cost = min( cost, ancestor[u][index].cost );
        u = ancestor[u][index].ancestor;
    }
    assert( depth[u] == depth[v] );
    if( u == v ) return cost;
    
    int index = 31 - __builtin_clz((unsigned) depth[u]) + 1; // balancear o index-- do começo
    while( ancestor[u][0].ancestor != ancestor[v][0].ancestor ) {
        index--;
        if( ancestor[u][index].ancestor == ancestor[v][index].ancestor )
            continue;
        cost = min( cost, ancestor[u][index].cost );
        cost = min( cost, ancestor[v][index].cost );
        u = ancestor[u][index].ancestor;
        v = ancestor[v][index].ancestor;
    }
    cost = min( cost, ancestor[u][0].cost );
    cost = min( cost, ancestor[v][0].cost );
    return cost;
}

int main() {
    scanf( "%d%d%d", &C, &P, &Q );
    for( int i = 0; i < P; ++i ) {
        int a, b, custo;
        scanf( "%d%d%d", &a, &b, &custo );
        city[a].push_back({custo, a, b});
        city[b].push_back({custo, b, a});
    }

    minimum_spanning_tree();
    least_common_ancestor_init();

    for( int i = 0; i < Q; ++i ) {
        int a, b;
        scanf( "%d%d", &a, &b );
        printf( "%d\n", solve(a, b) );
    }
    return 0;
}

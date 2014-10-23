/* D.a.cpp
 * Problema da etapa regional da maratona de 2014
 */

#include <stdio.h>
#include <limits.h>
#include <vector>
#include <algorithm>
#include <stack>
#include <list>

using std::pair;
using std::stack;
using std::list;
using std::vector;

typedef pair<int, int> node_t;
#define tnode first
#define lenght second

vector<node_t> nodes[10001];
int distance[10001];
int parent[10001];
int cycle[10001];
bool visited[10001];

int S, T; // número de Salões e Túneis
int X; // salão de entrada
int M; // comprimento da Dona Minhoca

/* dfs(i, j) retorna o tamanho do ciclo ao qual i pertence, informando que
 * distância entre este nodo e a anterior é j. */
int dfs( int node, int previous = 0 ) { 
    if( visited[node] ) { // Encontramos um ciclo
        cycle[node] = distance[parent[node]] - distance[node] + previous;
        return cycle[node];
    }
    visited[node] = true;
    distance[node] = distance[parent[node]] + previous;
    int cycle_size = 0;
    for( auto next : nodes[node] ) {
        if( next.tnode == parent[node] ) continue;
        parent[next.tnode] = node;
        int next_cycle = dfs( next.tnode, next.lenght );
        if( next_cycle != 0 && cycle[node] == 0 )
            cycle_size = cycle[node] = next_cycle;
    }
    return cycle_size;
}

void dfs() {
    for( int i = 0; i <= S; ++i )
        parent[i] = distance[i] = cycle[i] = visited[i] = 0;

    dfs(1);
}

bool not_closer( int n1, int n2 ) { // min-heap
    return distance[n1] > distance[n2];
}

void dijkstra( int start ) {
    vector<int> q = {start};
    for( int i = 0; i <= S; ++i ) {
        visited[i] = false;
        distance[i] = INT_MAX;
    }
    distance[start] = 0;

    while( !q.empty() ) {
        std::pop_heap( q.begin(), q.end(), not_closer );
        int current = q.back();
        q.pop_back();
        if( visited[current] ) continue;
        visited[current] = true;
        for( auto next : nodes[current] ) {
            if( visited[next.tnode] ) continue;
            if( distance[next.tnode] == INT_MAX ) q.push_back( next.tnode );
            distance[next.tnode] = std::min( distance[next.tnode], distance[current] + next.lenght );
        }
        std::make_heap( q.begin(), q.end(), not_closer );
    }
}
        

int solve( int start, int size ) {
    dijkstra( start );

    int best = INT_MAX;
    for( int i = 1; i <= S; ++i )
        if( cycle[i] >= size )
            best = std::min( best, 2*distance[i] + cycle[i] );

    return best == INT_MAX ? -1 : best;
}

int main() {
    scanf( "%d %d", &S, &T );

    for( int i = 0; i < T; ++i ) {
        int A, B, C;
        scanf( "%d %d %d", &A, &B, &C );
        nodes[A].push_back({B, C});
        nodes[B].push_back({A, C});
    }
    dfs();

    int Q;
    scanf( "%d", &Q );
    while( Q-- ) {
        scanf( "%d%d", &X, &M );
        printf( "%d\n", solve( X, M ) );
    }

    return 0;
}

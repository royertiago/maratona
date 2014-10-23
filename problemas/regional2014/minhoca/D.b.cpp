/* D.b.cpp
 * Problema da etapa regional da Maratona de 2014.
 *
 * Implementação equivalente ao arquivo anterior, mas usando
 * std::set para implementar Dijkstra, e fazendo a busca em
 * profundidade não-recursiva. */
#include <stdio.h>
#include <set>
#include <vector>
#include <utility>
#include <assert.h>

typedef std::pair<int, int> pii;
#define weight first
#define target second

int min( int i, int j ) { return i < j ? i : j; }

std::vector<pii> graph[10*1000];
int cycle[10*1000];
int distance[10*1000];
int parent[10*1000];
bool visited[10*1000];
int S, T;

// Calcula o tamanho de cada ciclo.
void dfs() {
    for( int i = 0; i < S; ++i ) 
        distance[i] = parent[i] = cycle[i] = visited[i] = 0;

    std::vector<pii> stack;
    stack.push_back({0, 0});
    cycle[0] = 0;
    visited[0] = true;

    /* A pilha conterá uma lista de pares (nodo analisado, próximo filho). */
    while( !stack.empty() ) {
        pii next = stack.back();
        stack.pop_back();

        int current = next.first;
        if( graph[current].size() == next.second ) continue;

        stack.push_back({current, next.second+1}); // já engatilhamos a próxima recursão

        int child = graph[current][next.second].target;
        int weight = graph[current][next.second].weight;

        if( child == parent[current] ) {
            continue;
        }

        if( visited[child] ) { // Econtramos um ciclo!
            if( cycle[child] != 0 ) continue; // Já analisamos este ciclo.
            int cycle_size = distance[current] - distance[child] + weight;
            cycle[child] = cycle_size;
            int node = current;
            while( node != child ) {
                cycle[node] = cycle_size;
                node = parent[node];
            }
            continue;
        }

        parent[child] = current;
        visited[child] = true;
        distance[child] = distance[current] + weight;
        stack.push_back({child, 0});
    }
}

bool closer( int i, int j ) {
    if( distance[i] != distance[j] ) return distance[i] < distance[j];
    return i < j;
}

void dijkstra( int source ) {
    for( int i = 0; i < S; ++i ) {
        distance[i] = 1000*1000+1;
        visited[i] = false;
    }

    std::set< int, bool(*)(int, int) > queue( closer );
    queue.insert(source);
    distance[source] = 0;
    visited[source] = true;

    while( !queue.empty() ) {
        int current = *queue.begin();
        queue.erase(current);
        visited[current] = true;
        for( auto p : graph[current] ) {
            if( visited[p.target] ) continue;
            queue.erase(p.target);
            distance[p.target] = min( distance[p.target], distance[current] + p.weight );
            queue.insert(p.target);
        }
    }
}

int main() {
    scanf( "%d%d", &S, &T );
    for( int i = 0; i < T; ++i ) {
        int a, b, w;
        scanf( "%d%d%d", &a, &b, &w );
        a--; b--;
        graph[a].push_back({w, b});
        graph[b].push_back({w, a});
    }
    dfs();
    int Q;
    scanf( "%d", &Q );
    while( Q-- ) {
        int source, lenght;
        scanf( "%d%d", &source, &lenght );
        dijkstra( source-1 );

        int best = 2*1000*1000+1;
        for( int i = 0; i < S; ++i )
            if( cycle[i] >= lenght )
                best = min( best, 2*distance[i] + cycle[i] );
        if( best == 2*1000*1000+1 )
            printf( "-1\n" );
        else
            printf( "%i\n", best );
    }
    return 0;
}

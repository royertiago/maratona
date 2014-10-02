#include <stdio.h>
#include <list>

using std::list;

#define SIZE 20001

list<int> nodes[SIZE];
int distance[SIZE];
bool visited[SIZE];
int parent[SIZE];
int side[SIZE];
int ancestor[SIZE][16]; //ancestor[node][j] é um ancestral de [node], distante [i] de [node].
int best_cache[SIZE], second_cache[SIZE];
int N, root;

int greatest_depth, second_greatest_depth;
int * opposite_cache( int node_side ) {
    if( node_side == greatest_depth ) return second_cache;
    return best_cache;
}
int * correct_cache( int node_side ) {
    if( node_side != greatest_depth ) return second_cache;
    return best_cache;
}

void dfs( int node, int dist ) {
    if(visited[node]) return;
    visited[node] = true;
    distance[node] = dist;
    for(int next : nodes[node])
        if(!visited[next]) {
            parent[next] = node;
            dfs( next, dist+1 );
        }
}

int root_dfs( int node, int previous, int dist, int Side ) {
    if( visited[node] ) return 0;
    visited[node] = true;
    parent[node] = previous;
    distance[node] = dist;
    side[node] = Side;
    int max = dist;
    for(int next: nodes[node]) {
        int tmp = root_dfs( next, node, dist+1, Side );
        max = max > tmp ? max : tmp;
    }
    return max;
}

void compute_cache( int node ) {
    if( visited[node] ) {
        return;
    }
    visited[node] = true;
    correct_cache(side[node])[distance[node]] = node;
    ancestor[node][0] = parent[node];
    int current = parent[node];
    for( int i = 1; (1 << i) <= distance[node]; ++i ) {
        compute_cache(current);
        ancestor[node][i] = ancestor[current][i-1];
        current = ancestor[node][i];
    }
}

int main() {
    int Q;
    scanf( "%d %d", &N, &Q );
    int a, b;
    for( int i = 1; i < N; ++i ) {
        scanf( "%d%d", &a, &b );
        nodes[a].push_back(b);
        nodes[b].push_back(a);
    }
    for( int i = 0; i <= N; ++i )
        distance[i] = visited[i] = 0;
    dfs( 1, 0 );

//  printf( "1st DFS results:\n" );
//  for( int i = 1; i <= N; ++i )
//      printf( "Node %d, dist %i, parent %i\n", i, distance[i], parent[i] );

    int max = 0;
    for( int i = 0; i <= N; ++i ) {
        if( distance[i] > max ) {
            max = distance[i];
            root = i;
        }
        distance[i] = visited[i] = 0;
    }
    dfs( root, 0 );

//  printf( "2nd DFS results:\n" );
//  for( int i = 1; i <= N; ++i )
//      printf( "Node %d, dist %i, parent %i\n", i, distance[i], parent[i] );

    max = 0;
    root = 0;
    for( int i = 1; i <= N; i++ )
        if( distance[i] >= max ) {
            max = distance[i];
            root = i;
        }

    while( distance[root] != max/2 )
        root = parent[root];
    /* Neste momento, root contém o nodo mais ao centro da árvore.
     * Note que utilizamos root para três coisas diferentes até agora. */

//  printf( "Chosen root: %d\n", root );

    for( int i = 0; i <= N; ++i )
        side[i] = distance[i] = visited[i] = 0;

    visited[root] = true;
    int current_best = 0, second_best = 0;
    for( int next: nodes[root] ) {
        int depth = root_dfs( next, root, 1, next );
        if( depth >= current_best ) {
            second_greatest_depth = greatest_depth;
            greatest_depth = next;
            current_best = depth;
        } else if( depth >= second_best ) {
            second_greatest_depth = next;
            second_best = depth;
        }
    }

    for( int i = 0; i <= N; ++i ) {
        second_cache[i] = best_cache[i] = visited[i] = 0;
        for( int j = 1; j < 15; ++j )
            ancestor[i][j] = 0;
    }
    visited[root] = true;
    best_cache[0] = second_cache[0] = root;
    for( int i = 1; i <= N; ++i )
        compute_cache(i);

//  printf( "Cache 1:\n" );
//  for( int i = 0; best_cache[i] != 0; ++i )
//      printf( "%i - %i\n", i, best_cache[i] );
//  printf( "Cache 2:\n" );
//  for( int i = 0; second_cache[i] != 0; ++i )
//      printf( "%i - %i\n", i, second_cache[i] );


    while( Q-- ) {
        int vertex, query;
        scanf( "%d %d", &vertex, &query );
        if( query > max ) printf( "0\n" );
        else if( query >= distance[vertex] )
            printf( "%d\n", opposite_cache(side[vertex])[query - distance[vertex]] );
        else {
            int current = vertex;
            for( int i = 0; query != 0; i++, query >>= 1 )
                if( query % 2 != 0 )
                    current = ancestor[current][i];

            printf( "%d\n", current );
        }
    }
    return 0;
}

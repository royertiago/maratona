/* justice.cpp
 * Problema J da etapa nacional da Maratona de 2007.
 */
#include <stdio.h>
#include <vector>
#include <algorithm>

struct node {
    std::vector<int> edges;
    bool used;
    int i;
} nodes[100*1000];
node * graph[100*1000];

int H, R;

bool comp( node * a, node * b ) {
    return a->edges.size() > b->edges.size();
}

int main() {
    while( scanf("%d%d", &H, &R ) != EOF && H != 0 ) {
        for( int i = 0; i < H; ++i ) {
            graph[i] = &nodes[i];
            nodes[i].edges.clear();
            nodes[i].used = false;
            nodes[i].i = i+1;
        }
        for( int i = 0; i < R; ++i ) {
            int a, b;
            scanf( "%d%d", &a, &b );
            nodes[a-1].edges.push_back(b-1);
            nodes[b-1].edges.push_back(a-1);
        }

        /* Uma liga da justiça é um clique máximo, tal que todas as arestas do
         * grafo possuem ao menos uma extremidade no clique.
         * Se n é o tamanho do clique, todos os nodos fora do clique
         * possuem grau menor ou igual a n. Podemos fortalecer isso para
         * menor que n: caso algum vértice possua tamanho igual a n,
         * podemos juntá-lo à clique, aumentando seu tamanho.
         *
         * O primeiro laço procura qual o maior clique que dá para encontrar
         * no grafo, usando os nodos de maior grau. O segundo laço testa se
         * existe algum nodo fora do clique que possui aresta para outro nodo
         * fora do clique. */
        std::sort( graph, graph + H, comp );
        graph[0]->used = true;
        int i;
        for( i = 1; i < H; ++i ) {
            int count = 0;
            for( int k : graph[i]->edges )
                count += nodes[k].used;
            if( count != i ) break;
            graph[i]->used = true;
        }
        for( ; i < H; ++i )
            for( int k : graph[i]->edges )
                if( !nodes[k].used ) {
                    printf( "N\n" );
                    goto next;
                }
        printf( "Y\n" );
next:;
    }
    return 0;
}

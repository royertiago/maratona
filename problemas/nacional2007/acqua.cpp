/* acqua.cpp
 * Problema A do aquecimento da etapa nacional da Maratona de 2007.
 *
 * Menor ancestral comum.
 *
 * Cada seção (ou encontro com o mar) é um nodo. Para determinar se
 * dois nós estão na mesma árvore, adicionamos um nodo artificial
 * que será o pai de todas as raízes das árvores; o menor ancestral
 * comoum a dois nodos em árvores diferentes será este nodo artificial.
 */
#include <stdio.h>
#include <vector>

#define MAX 1001
#define MAX2 1024 // Primeira podência de 2 maior que max

// Árvore de segmentos
template< typename T >
struct segment_tree_t {
    T data[4*MAX2];
    unsigned size;
    T (*op)(T, T);

    /* Constrói (ou reconstrói) a árvore de segmentos. */
    void rebuild( const T * new_source, unsigned new_size ) {
        size = new_size;
        build( 1, size, 1, new_source );
    }

    /* build
     * Função usada na inicialização da árvore.
     */
    T build( unsigned min, unsigned max, unsigned index, const T * source ) {
        if( min == max )
            return data[index] = source[min];
        unsigned half = min + (max-min)/2;
        return data[index] = op( build(min, half, 2*index, source),
                                 build(half+1, max, 2*index+1, source) );
    }

    /* Retorna op(a, a+1, a+2, ..., b). */
    T query( unsigned a, unsigned b ) const {
        return query( a, b, 1, size, 1 );
    }

    /* Retorna op(a, a+1, ..., b).
     * min, max e index são usados internamente para controle.
     *
     * Hipóteses: min <= a <= b <= size, index corresponde ao nodo
     * da árvore de segmentos de domínio min, max. */
    T query( unsigned a, unsigned b, 
             unsigned min, unsigned max, unsigned index ) const {
        unsigned half = min + (max-min)/2;
        if( a == min && b == max )
            return data[index];
        if( b <= half )
            return query( a, b, min, half, 2*index );
        if( a > half )
            return query( a, b, half+1, max, 2*index+1 );
        return op( query(a, half, min, half, 2*index),
                    query(half+1, b, half+1, max, 2*index+1) );
    }
};

std::vector<int> edges[MAX];
bool visited[MAX];
int C, R, S, Q;

// Estruturas para a busca do menor ancestral comum (least common ancestor)
struct lca_pair {
    int node;
    int height;
} lca_data[MAX*2-1];
int lca_max;
int lca_index[MAX];

void recursive_build( int, int );

void build_lca_structure() {
    lca_max = 0;
    for( int i = 0; i <= C; i++ )
        visited[i] = false;

    recursive_build( 0, 0 );
}

void recursive_build( int node, int height ) {
    visited[node] = true;
    lca_index[node] = lca_max;
    lca_data[lca_max++] = {node, height};

    for( int next : edges[node] ) {
        if( visited[next] ) continue;
        recursive_build( next, height + 1 );
        lca_data[lca_max++] = {node, height};
    }
}

segment_tree_t<lca_pair> lca_segtree;

// Operação que será usada nesta árvore específica
lca_pair lca_pair_min( lca_pair a, lca_pair b ) {
    return a.height < b.height ? a : b;
}

int main() {
    lca_segtree.op = lca_pair_min;
    while( scanf("%d%d%d%d", &C, &R, &S, &Q) != EOF && C != 0 ) {
        for( int i = 0; i <= C; ++i )
            edges[i].clear();
        
        int c;
        for( int i = 0; i < R; ++i ) {
            scanf( "%d", &c );
            edges[0].push_back( c );
            edges[c].push_back( 0 );
        }
        int d;
        for( int i = 0; i < S; ++i ) {
            scanf( "%d%d", &c, &d );
            edges[c].push_back( d );
            edges[d].push_back( c );
        }

        build_lca_structure();
        lca_segtree.size = lca_max - 1;
        lca_segtree.rebuild( lca_data, lca_segtree.size );

        printf( "\n" );
        while( Q-- ) {
            scanf( "%d%d", &c, &d );
            int a = lca_index[c] < lca_index[d] ? lca_index[c] : lca_index[d];
            int b = lca_index[c] < lca_index[d] ? lca_index[d] : lca_index[c];
            int node = lca_segtree.query(a, b).node;
            int ans;
            if( node == 0 ) ans = -1;
            else if( node == c || node == d ) ans = 0;
            else ans = node;
            printf( "%d\n", ans );
        }
    }
    return 0;
}

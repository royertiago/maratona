/* G.cpp
 * Problema da etapa regional da Maratona de 2013.
 */
#include <stdio.h>
#include <assert.h>
#include <algorithm>

int container[300][300];
int l[300], c[300];
unsigned L, C;

/* Para ordenar os conteineres, não precisamos trocar todos os contêineres
 * de lugar, basta trocar os índices.
 * Como precisamos indexar tando por linha quanto por coluna (e trocar 
 * ambos os índices), usaremos dois vetores de índices: um para linhas (l) e
 * um para colunas (c).
 *
 * O código para fazer a contagem é o mesmo para ambos os vetores de índices.
 *
 * As primeiras linhas inicializam o vetor com seus índices normais e ordenam
 * o vetor. A função de comparação compara os elementos de cada índice; como
 * o vetor passado é o de índices, apenas os índices são ordenados, sem tocar
 * na matriz de contêineres.
 *
 * Desta forma, sabemos que quem deve ocupar a coluna (ou linha) i da matriz
 * é a atual linha v[i]. E quem deve ocupar a coluna v[i] é a atual linha v[v[i]].
 * E assim por diante. As últimas linhas do vetor encontram estes ciclos;
 * para um ciclo de tamanho n, são necessárias n-1 trocas. É o somatório
 * destes números o valor retornado.
 */
unsigned minimum_swaps( int * v, unsigned size, bool (*f)( int , int ) ) {
    static bool visited[300];
    for( unsigned i = 0; i < size; ++i ) {
        v[i] = i;
        visited[i] = 0;
    }

    std::sort( v, v + size, f );

    unsigned swaps = 0;
    for( unsigned i = 0; i < size; ++i ) {
        if( visited[i] ) continue;
        visited[i] = true;
        int j = v[i];
        while( !visited[j] ) {
            visited[j] = true;
            swaps++;
            j = v[j];
        }
    }
    return swaps;
}

bool f( int i, int j ) {
    return container[i][0] < container[j][0];
}
bool g( int i, int j ) {
    return container[0][i] < container[0][j];
}

bool valid() {
    int v = 1;
    for( unsigned i = 0; i < L; ++i )
    for( unsigned j = 0; j < C; ++j )
        if( container[l[i]][c[j]] != v++ )
            return false;
    return true;
}

int main() {
    scanf( "%u%u", &L, &C );
    for( unsigned i = 0; i < L; ++i )
    for( unsigned j = 0; j < C; ++j )
        scanf( "%d", &container[i][j] );

    unsigned swaps = minimum_swaps( l, L, f ) + minimum_swaps( c, C, g );
    if( valid() )
        printf( "%u\n", swaps );
    else
        printf( "*\n" );

    return 0;
}

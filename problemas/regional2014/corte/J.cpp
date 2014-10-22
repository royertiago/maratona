/* J.cpp
 * Problema da etapa regional da Maratona de 2014.
 *
 * Programação dinâmica.
 */
#include <stdio.h>
#include <cmath>
#include <utility>
#include <algorithm>

typedef std::pair<double, double> Coord;
#define MAX 200
#define INFTY 1e20
#define SQR(x) (x)*(x)

Coord coord[MAX];
double pd[MAX][MAX];
double pdt[MAX][MAX];
/* pd[i][j] é a maneira mais económica de repartir o polígono
 * i, i+1, ..., j em quadriláteros, e pdt[i][j] é a maneira
 * mais econômica de partir o mesmo polígono em quadriláteros e
 * em um triângulo, com a aresta ij pertencendo ao triângulo.
 * Caso tais cortes não sejam possíveis, pd[i][j] e pdt[i][j]
 * (respectivamente) conterão INFTY.
 *
 * O propósito de existência de pdt é ser uma cache para o laço
 * interno do algoritmo; veja abaixo. */
int N;
double d[MAX][MAX]; // d[i][j]é a distância entre as coordenadas i e j.

/* Retorna a maneira mais econômica de passar um corte pelos vértices
 * i, i+1, ..., j, e cortar o polígono composto por estes vértices
 * em quadriláteros. (Ou INFTY se não for possível fazer a decomposição.)
 *
 * Assumiremos que i < j e que pd[i][j] já esteja computado. */
double single_cut( int i, int j ) {
    if( i+1 == j ) return 0;
    if( (j - i + 1) % 2 == 1 ) return INFTY;
    return pd[i][j] + d[i][j];
}

/* Retorna a maneira mais econômica de escolher um vertice k,
 * i < k < j, passar dois cortes (um de i até k e outro de k
 * até j) e subdividir os polígonos i, i+1, ..., k e k, k+1 ..., j
 * em quadriláteros. (Ou INFTY se não existir k que permita
 * tal decomposição.) Isto é,
 *  double_cut(i, j) ==    min    single_cut(i, k) + single_cut(k, j)
 *                      i < k < j
 *
 * Assumiremos que i < j e que pdt[i][j] já esteja computado. */
double double_cut( int i, int j ) {
    if( i+2 == j ) return 0;
    if( (j - i + 1) % 2 == 0 ) return INFTY;
    return pdt[i][j];
}

double solve() {
    for( int i = 0; i < N; ++i )
        for( int j = 0; j < N; ++j )
            d[i][j] = std::sqrt( SQR(coord[i].first - coord[j].first) +
                                SQR(coord[i].second - coord[j].second) );

    for( int i = 0; i + 3 < N; ++i ) {
        pd[i][i+3] = 0.0;
        pdt[i][i+3] = INFTY;
        /* Não precisamos incluir todos os casos bases pois
         * usaremos as funções single_cut e double_cut, que
         * tratarão desse problema para nós. */
    }
    for( int v = 4; v < N; ++v )
        for( int u = 0; u + v < N; ++u ) {
            int i = u, j = u + v;
            pd[i][j] = pdt[i][j] = INFTY;
            /* A essência do algoritmo está em otimizar o seguinte código:
             *  for( int k = i + 1; k < j; ++k )
             *      for( int l = k + 1; l < j; ++l )
             *          pd[i][j] = std::min( pd[i][j],
             *                  single_cut(i, k) + 
             *                  single_cut(k, l) +
             *                  single_cut(l, j) );
             * Note que, dentro do laço interno, single_cut(i, k) não se
             * altera; o laço interno otimiza a soma single_cut(k, l) +
             * single_cut(l, j). Fixado um j e um k, podemos ver que esta
             * soma é otimizada uma vez para cada i; pdt[k][j] armazena
             * este ótimo, e usamos double_cut para acessá-lo e remover
             * o laço interno, baixando a complexidade de n**4 para n**3. */
             for( int k = i + 1; k < j; ++k ) {
                 pd[i][j] = std::min( pd[i][j],
                         single_cut(i, k) + double_cut(k, j) );
                 pdt[i][j] = std::min( pdt[i][j],
                         single_cut(i, k) + single_cut(k, j) );
             }
        }
    return pd[0][N-1];
}

int main() {
    scanf( "%d", &N );
    N *= 2;
    for( int i = 0; i < N; ++i )
        scanf( "%lf%lf", &coord[i].first, &coord[i].second );

    printf( "%.4lf\n", solve() );
}

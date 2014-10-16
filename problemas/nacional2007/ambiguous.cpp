/* ambiguous.cpp
 * Problema A da etapa nacional da Maratona de 2007.
 *
 * Algoritmo:
 * Exemplo: AB, BA, ABA. Podemos formar a string ABABA de dois jeitos:
 * A B|A B A
 * A B A|B A
 * Podemos considerar o problema como uma sucessão de encaixes. Primeiro,
 * começamos com AB:
 * -AB
 * -
 * Agora, adicionamos o bloco ABA abaixo dele:
 * -AB
 * -ABA
 * Agora, encaixamos ABA acima:
 * -ABABA
 * -ABA
 * Por fim, encaixamos BA embaixo:
 * -ABABA
 * -ABABA
 * Do ponto de vista do grafo, não é importante quais são os caracteres
 * que já foram encaixados, mas sim apenas o que falta encaixar. Então,
 * o primeiro passo pode ser codificado como (AB, 0): isto é, vamos encaixar
 * com AB, e já completamos 0 desses caracteres. O segundo estado é
 * (ABA, 2), o terceiro (ABA, 1), e o quarto, (BA, 2).
 * Note que a única coisa que precisamos manter é o estado. Modelamos
 * isso por um problema de grafos: um estado (w, n) liga-se a um estado (x, m)
 * se x possuir um prefixo de tamanho |w| - n que é sufixo de w (isto é, as 
 * primeiras |w| - n letras de x são iguais às últimas letras de w)
 * e o que sobrar possui tamanho m. Neste caso, a aresta possui peso |w| - n
 * (pois adicionamos |w| - n letras à sequência).
 * Também há o caso em que existe uma subcadeia de tamanho m começando
 * em n em w; neste caso, adicionamos uma aresta de peso m entre (w, m)
 * e (w, m + n).
 *
 * Agora, basta rodar Dijkstra e descobrir qual o caminho mais curto entre
 * algum (w, 0) até algum (w, |w|). Para isso, inserimos todos os (w, 0)
 * na fila, como se tivéssemos adicionado um vértice "source" com distância
 * zero até todos esses vértices.
 *
 * Note por último que não é necessario armazenar a informação sobre qual a
 * string armazenada nem qual o índice atual; para isso funcionar, adicionamos
 * a lista de ponteiros snode. snode[i][j] corresponde a (wi, j).
 */
#include <stdio.h>
#include <string.h>
#include <vector>
#include <utility>
#include <limits.h>
#include <set>

#define target first
#define weight second

#define MAXSTRING 100
#define MAXLENGTH 50
#define MAX (MAXSTRING * (MAXLENGTH+1))

struct node_t {
    std::vector<std::pair<int, int>> edges;
    bool terminal;
    int distance; // dijkstra
    bool visited;
    int i;
} node[MAX];

node_t * snode[MAXSTRING][MAXLENGTH+1];
char strings[MAXSTRING][MAXLENGTH+1];
int len[MAXSTRING];

int N, V;

int min( int i, int j ) { return i < j ? i : j; }

/* Compara as duas strings; exemplo:
 * sublen( "AAB", "AAC" ) == 0 pois nem "AAB" é prefixo de "AAC" nem vice-versa
 * sublen( "AAB", "AA" ) == -2
 * sublen( "AA", "AAC" ) == 2 */
int sublen( char * c, char * d ) {
    int diff = 0;
    while( *c != '\0' && *d != '\0' ) {
        if( *c++ != *d++ ) return 0;
        diff++;
    }
    if( *c == '\0' ) return diff;
    return -diff;
}

void generate_graph() {
    int n = 0;
    for( int i = 0; i < N; ++i )
        for( int j = 0; j <= len[i]; ++j ) {
            node[n].terminal = j == len[i];
            node[n].edges.clear();
            snode[i][j] = &node[n];
            node[n].i = n;
            n++;
        }
    V = n;
    for( int i = 0; i < N; ++i ) {
        char * a = strings[i];
        for( int k = 1; k < len[i]; ++k ) { // k começa de 1; não teremos laços
            int l = sublen( a + k, a );
            if( l != 0 )
                snode[i][k]->edges.push_back({ snode[i][l]->i, l });
        }
        for( int j = 0; j < N; ++j ) {
            if( j == i ) continue; // Já resolvemos no laço acima.
            char * b = strings[j];
            for( int k = 0; k < len[i]; ++k ) {
                int l = sublen( a + k, b );
                if( l == 0 ) continue;
                if( l > 0 ) // a+k é prefixo de b
                    snode[i][k]->edges.push_back({ snode[j][l]->i, l });
                else // b é prefixo de a+k
                    snode[i][k]->edges.push_back({ snode[i][k - l]->i, -l });
            }
        }
    }
}

bool cmp( node_t * a, node_t * b ) {
    if( a->distance != b->distance )
        return a->distance < b->distance;
    else
        return a->i < b->i;
}

int solve() {
    std::set< node_t *, bool (*) (node_t*, node_t*) > queue( cmp );
    for( int i = 0; i < N; ++i ) {
        queue.insert( snode[i][0] );
        for( int j = 0; j <= len[i]; ++j ) {
            snode[i][j]->distance = j == 0 ? 0 : INT_MAX;
            snode[i][j]->visited = false;
        }
    }
    while( !queue.empty() ) {
        node_t * current = *queue.begin();
        queue.erase( current );
        current->visited = true;

        for( auto edge : current->edges ) {
            node_t * next = & node[edge.target];
            if( next->visited )
                continue;
            queue.erase( next );
            next->distance = min( next->distance, current->distance + edge.weight );
            queue.insert( next );
        }
    }
    int best = INT_MAX;
    for( int i = 0; i < N; ++i )
        best = min( best, snode[i][len[i]]->distance );
    return best == INT_MAX ? -1 : best;
}

int main() {
    while( scanf("%d", &N) != EOF && N != 0 ) {
        for( int i = 0; i < N; ++i ) {
            scanf( "%s", &strings[i][0] );
            len[i] = (int) strlen(strings[i]);
        }
        generate_graph();
        printf( "%d\n", solve() );
    }
    return 0;
}

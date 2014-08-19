/* 501.cpp
 * Problema: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=442
 * Mirror: https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3646
 */
#include <stdio.h>
#include <set>

// Classe que controlará as transações da black box
struct transaction {
    int * A;
    int * u;
    int count; // Número de elementos já adicionados
    int m, n; // Limite da transação - são decrementados

    /* true caso já terminaram-se as transações. */
    bool end() {
        return m == 0 && n == 0;
    }

    /* true se a próxima transação é um ADD, false caso contrário.
     * Este código só deve ser executado uma vez por instrução. */
    bool add() {
        if( n == 0 || *u != count ) {
            m--;
            count++;
            return true;
        }
        u++;
        n--;
        return false;
    }

    /* Retorna o valor do ADD, caso transaction::add() tenha retornado true */
    int next() {
        return *A++;
    }
};

void solve( transaction t ) {
    std::multiset<int> list = {2100000001};
    auto ref = list.insert( 2000000001 );
    /* ref é um "ponteiro" que apontará para o valor que será o próximo
     * i-ésimo da lista, a ser escrito no caso de um GET.
     * Apenas deslocaremos ref para frente e para trás, de acordo com
     * o inteiro que estamos inserindo. */

    while( !t.end() )
        if( t.add() ) {
            int k = t.next();
            list.insert( k );
            if( k < *ref )
                --ref;
        }
        else {
            printf( "%i\n", *ref );
            ++ref;
        }
}

int main() {
    int T, m, n, A[30000], u[30000];

    scanf( "%d", &T );
    for( int i = 0; i < T; ++i ) {
        if( i != 0 ) printf( "\n" );
        scanf( "%d %d", &m, &n );

        for( int j = 0; j < m; ++j )
            scanf( "%d", &A[j] );
        for( int j = 0; j < n; ++j )
            scanf( "%d", &u[j] );
        
        solve( {A, u, 0, m, n} );
    }
    return 0;
}

/* icpc.c.cpp
 * Problema I da etapa nacional da Maratona de 2007.
 *
 * Mesma estratégia de icpc.c.cpp, mas isolando a busca binária.
 */
#include <stdio.h>
#include <algorithm>

int penalty;
#define MAX_PENALTY (10 * 300 + 1)

struct team {
    int acc, wa, time;
    bool operator<( team t ) const {
        if( acc != t.acc ) return acc > t.acc;
        return operator()(penalty) < t(penalty);
    }
    bool operator==( team t ) const {
        return acc == t.acc && operator()(penalty) == t(penalty);
    }
    int operator()( int p ) const {
        return wa * p + time;
    }
} teams[100], aux[100];

int T, P;

bool predicate( int p ) {
    penalty = p;
    std::sort( aux, aux + T );

    for( int i = 0; i+1 < T; ++i ) {
        if( teams[i].acc != teams[i+1].acc ) continue;
        if( !(teams[i] == aux[i]) ) return false;
        if( teams[i](20) == teams[i+1](20) && !(aux[i] == aux[i+1]) ) return false;
        if( teams[i](20) < teams[i+1](20) && !(aux[i] < aux[i+1]) ) return false;
        if( teams[i+1](20) <  teams[i](20) && !(aux[i+1]  < aux[i]) ) return false;
    }
    return true;
}

bool not_predicate( int p ) {
    return not predicate( p );
}

/* Dado um intervalo [min, max] tal que pred(max) é true, esta
 * função retorna o menor x neste intervalo que satisfaz pred(x).
 * Assumiremos que min <= max e que pred é monotônico. */
int binary_search( int min, int max, bool (*pred)(int) ) {
    // Manteremos a invariante de que pred(max) == true.
    while( min < max ) {
        int middle = min + (max - min)/2; // Arredondamos para baixo
        if( pred(middle) )
            max = middle;
        else
            min = middle + 1;
    }
    return max;
}

/* Dado um limite mínimo min, encontra o primeiro valor no intervalo
 * [min, infty) que satisfaz o predicado passado.
 * Para evitar laços intermináveis, maximum é provido como máximo
 * absoluto da busca. */
int unbounded_binary_search( int min, bool (*pred)(int), int maximum ) {
    int max = min <= 0 ? 1 : 2 * min;
    while( !pred(max) )
        if( max > maximum ) return maximum;
        else max *= 2;
    // Aqui, pred(max) é verdadeiro. Basta uma busca binária:
    return binary_search( min, max, pred );
}

int main() {
    while( scanf("%d%d", &T, &P) != EOF && T != 0 ) {
        for( int i = 0; i < T; ++i ) {
            int A, S;
            teams[i] = {0, 0, 0};
            for( int j = 0; j < P; ++j )
                if( scanf("%d/%d", &A, &S) == 2 ) {
                    teams[i].acc++;
                    teams[i].wa += A;
                    teams[i].time += S;
                }
        }

        penalty = 20;
        std::sort( teams, teams + T );
        std::copy( teams, teams + T, aux );

        // Busca binária - primeiro termo
        printf( "%d ", binary_search(1, 20, predicate) );
        int value = unbounded_binary_search( 20, not_predicate, MAX_PENALTY );
        if( value == MAX_PENALTY )
            printf( "*\n" );
        else
            printf( "%d\n", value - 1 );
    }
    return 0;
}

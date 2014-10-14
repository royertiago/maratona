/* icpc.cpp
 * Problema I da etapa nacional da Maratona de 2007.
 *
 * Este arquivo resolve o problema usando busca linear.
 */
#include <stdio.h>
#include <algorithm>

int penalty, T, P;

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

/* Predicado; retorna true caso com a penalidade atual os times permanecem
 * na mesma ordem. */
bool pred() {
    std::sort( aux, aux + T );
    for( int i = 0; i + 1 < T; ++i ) {
        if( !(aux[i] == teams[i]) ) return false;
        if( aux[i].acc != aux[i+1].acc ) continue;
        if( aux[i] < aux[i+1] && teams[i](20) >= teams[i+1](20) ) return false;
        if( aux[i+1] < aux[i] && teams[i+1](20) >= teams[i](20) ) return false;
        if( aux[i+1] == aux[i] && teams[i+1](20) != teams[i](20) ) return false;
    }
    return true;
}

int main() {
    while( scanf("%d%d", &T, &P) != EOF && T != 0 ) {
        int A, S;
        for( int i = 0; i < T; i++ ) {
            teams[i].acc = teams[i].wa = teams[i].time = 0;
            for( int j = 0; j < P; ++j )
                if( scanf("%d/%d", &A, &S) == 2 ) {
                    teams[i].acc++;
                    teams[i].wa += A; // A e A-1 não faz diferença.
                    teams[i].time += S;
                }
        }

        penalty = 20;
        std::sort( teams, teams + T );
        for( int i = 0; i < T; ++i )
            aux[i] = teams[i];

        // Busca linear - encontrar o mínimo
        for( penalty = 20; ; --penalty )
            if( !pred() || penalty == 0 ) {
                printf( "%d ", penalty + 1 );
                break;
            }

        // Busca linear - encontrar o máximo
        for( penalty = 20; ; ++penalty )
            if( !pred() ) {
                printf( "%d\n", penalty - 1 );
                break;
            }
            else if( penalty > 10 * 300 + 1 ) {
                printf( "*\n" );
                break;
            }
    }
    return 0;
}

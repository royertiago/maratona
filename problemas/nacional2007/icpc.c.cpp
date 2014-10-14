/* icpc.c.cpp
 * Problema I da etapa nacional da Maratona de 2007.
 *
 * Mesma estratégia de icpc.b.cpp, mas com busca binária.
 */
#include <stdio.h>
#include <algorithm>

int penalty;

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

bool pred() {
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
        int min = 1, max = 20;
        while( min < max ) {
            // invariante: pred(max) == true.
            penalty = (min + max)/2; // Arredondamos em direção a min
            if( pred() ) {
                max = penalty;
            }
            else {
                min = penalty + 1;
            }
        }
        printf( "%d ", max );

        // Busca binária - limite superior para o segundo termo
        penalty = 40;
        while( pred() ) {
            if( penalty > 10 * 300 ) {
                printf( "*\n" );
                goto next;
            }
            penalty *= 2;
        }

        // Busca binária - segundo termo
        min = 20; max = penalty;
        while( min < max ) {
            // invariante: pred(min) == true
            penalty = (min + max + 1) / 2; // Arredondamos em direção a max
            if( pred() ) {
                min = penalty;
            }
            else {
                max = penalty - 1;
            }
        }
        printf( "%d\n", min );

next:; /* label usado para, simultaneamente, quebrar o laço do limite superior
       * e dar um 'continue' neste. */
    }
    return 0;
}

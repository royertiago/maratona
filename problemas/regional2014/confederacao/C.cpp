/* C.cpp
 * Problema da etapa regional da maratona de 2014
 */
#include <stdio.h>
#include <algorithm>

struct quadruple {
    int x, y, z, w;
    int operator*( quadruple t ) {
        return x*t.x + y*t.y + z*t.z;
    }
    /* GAMBIARRRA: para planetas, w será a tag usada para separar
     * os planetas por região. Para planos, w é o termo livre da equação.
     */
};

quadruple planos[500];
quadruple planetas[10000];

int main() {
    int M, N;
    scanf( "%d %d", &M, &N );
    for( int i = 0; i < M; ++i )
        scanf( "%d%d%d%d", &planos[i].x, &planos[i].y, &planos[i].z, &planos[i].w );
    for( int i = 0; i < N; ++i ) {
        scanf( "%d%d%d", &planetas[i].x, &planetas[i].y, &planetas[i].z );
        planetas[i].w = 0;
    }

    quadruple * const end = planetas + N;
    int max_tag = 1;

    for( quadruple * plano = planos; plano != planos + M; ++plano ) {
        quadruple * j = planetas;
        while( j != end ) {
            quadruple * k = std::find_if( j, end, [&](quadruple p){return p.w != j->w;} );
            quadruple * l = std::partition( j, k, [&](quadruple p){return p**plano > plano->w;} );
            while( l != k )
                l++->w = max_tag;
            ++max_tag;
            j = k;
        }
    }
    int max = 0, count = 0, last_tag = 0;
    for( int i = 0; i < N; ++i ) {
        if( planetas[i].w == last_tag )
            count++;
        else {
            max = std::max(count, max);
            count = 1;
            last_tag = planetas[i].w;
        }
    }
    max = std::max(count, max);

    printf( "%d\n", max );
    return 0;
}

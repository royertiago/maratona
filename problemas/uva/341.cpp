/* 341.cpp
 * Problema: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=277
 *
 * Algoritmo de Dijkstra.
 */
#include <stdio.h>
#include <limits.h>
#include <vector>
#include <algorithm>

#define NI 10

struct Intersection;
struct Street {
    int cost;
    Intersection * destiny;
};
struct Intersection {
    int id;
    int numStreets;
    int cost;
    bool analyzed;
    Intersection * previous;
    Street streets[NI];
};

bool closer( Intersection * i, Intersection * j ) {
    return i->cost > j->cost;
}

Intersection intersections[NI];

void init() {
    for( int i = 0; i < NI; ++i )
        intersections[i].id = i + 1;
}
void reset() {
    for( Intersection & i : intersections ) {
        i.numStreets = 0;
        i.cost = INT_MAX;
        i.analyzed = false;
    }
}

/* Roda Dijkstra começando no nó passado. */
void dijkstra( int starter ) {
    using namespace std;
    vector<Intersection *> queue;

    intersections[starter].cost = 0;
    intersections[starter].previous = &intersections[starter];
    intersections[starter].analyzed = true;
    queue.push_back( &intersections[starter] );

    while( !queue.empty() ) {
        pop_heap( queue.begin(), queue.end(), closer );
        Intersection * in = queue.back();
        queue.pop_back();

        for( int i = 0; i < in->numStreets; ++i ) {
            Intersection * jn = in->streets[i].destiny;
            if( in->cost + in->streets[i].cost < jn->cost ) {
                jn->cost = in->cost + in->streets[i].cost;
                jn->previous = in;
                if( !jn->analyzed ) {
                    queue.push_back( jn );
                    jn->analyzed = true;
                }
            }
        }
        make_heap( queue.begin(), queue.end(), closer );
    }
}

void printPath( int destiny ) {
    static Intersection * ints[NI];
    int i = NI - 1;
    ints[i] = &intersections[destiny];
    while( ints[i]->previous != ints[i] ) {
        ints[i-1] = ints[i]->previous;
        --i;
    }
    printf( "Path =" );
    for( ; i < NI; ++i )
        printf( " %i", ints[i]->id );

    printf( "; %i second delay\n", ints[NI-1]->cost );
}

int main() {
    int cases = 1;
    int num; // number of intersections
    int streets;
    int target, cost; // target intersection, traversal cost
    int begin, end; // searched intersections
    init();
    while( scanf("%d", &num) == 1 && num != 0 ) {
        reset();
        for( int i = 0; i < num; ++i ) {
            scanf( "%d", &streets );
            intersections[i].numStreets = streets;
            for( int j = 0; j < streets; ++j ) {
                scanf( "%d %d", &target, &cost );
                target--;
                intersections[i].streets[j].cost = cost;
                intersections[i].streets[j].destiny = &intersections[target];
            }
        }
        scanf( "%d %d", &begin, &end );
        printf( "Case %d: ", cases++ );
        dijkstra( begin - 1 );
        printPath( end - 1 );
    }
    return 0;
}

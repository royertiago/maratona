/* 1340.cpp
 * Problema: https://www.urionlinejudge.com.br/judge/en/problems/view/1340
 */

#include <stdio.h>
#include <queue>
#include <vector>

using std::priority_queue;
using std::queue;
using std::vector;

int main() {
    int opc;
    while( scanf("%d", &opc) == 1 ) {
        vector<int> vec;
        queue<int> q;
        priority_queue<int> pq;
        int op, val;
        bool mvec = true, mq = true, mpq = true; // May be a VECtor etc
        while( opc-- ) {
            scanf( "%i %i", &op, &val );
            if( op == 1 ) {
                if( mvec ) vec.push_back( val );
                if( mq )   q.push( val );
                if( mpq )  pq.push( val );
            } else {
                if( mvec ) if( vec.back() != val ) mvec = false; else vec.pop_back();
                if( mq )   if( q.front() != val ) mq = false; else q.pop();
                if( mpq )  if( pq.top() != val ) mpq = false; else pq.pop();
            }
        }
        if( mvec + mq + mpq >= 2 ) printf( "not sure\n" );
        else if( mvec + mq + mpq == 0 ) printf( "impossible\n" );
        else if( mvec ) printf( "stack\n" );
        else if( mq ) printf( "queue\n" );
        else printf( "priority queue\n" );
    }
    return 0;
}

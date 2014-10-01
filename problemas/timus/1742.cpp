/* 1742.cpp
 * Problem: http://acm.timus.ru/problem.aspx?num=1742
 */
#include <stdio.h>

int successor[100001];
bool has_predecessor[100001];
char cycle_type[100001]; // 'N'ot on cycle, 'O'n cycle, 'I'solated cycle
int timestamp[100001];

int n;

int main() {
    scanf( "%d", &n );
    for( int i = 1; i <= n; ++i ) {
        timestamp[i] = has_predecessor[i] = false;
        cycle_type[i] = 'N';
    }
    for( int i = 1; i <= n; ++i ) {
        scanf( "%d", &successor[i] );
        has_predecessor[successor[i]] = true;
    }

    int isolated_cycles = 0, // Number of cycles not reached by other nodes
        outside_cycles = 0,  // Number of nodes that are not in any cycle
        cycles = 0,          // Total number of cycles
        leaves = 0,          // Number of nodes that have no ancestors
        previous_timestamp = 0;
    /* The timestamp is used, when a cycle is found, whether it is a cycle
     * newly found or has already been visited. */

    // First, search all cycles
    for( int i = 1; i <= n; ++i ) {
        if( timestamp[i] != 0 ) continue;

        ++previous_timestamp;
        int j = i, k;
        while( timestamp[j] == 0 ) {
            timestamp[j] = previous_timestamp;
            k = j;
            j = successor[j];
        }
        if( timestamp[j] == previous_timestamp ) { // found a cycle
            cycles++;
            isolated_cycles += i == j;
            while( cycle_type[k] == 'N' ) {
                cycle_type[k] = i == j ? 'I' : 'O';
                k = successor[k];
            }
        } else if( cycle_type[j] == 'I' ) {
            isolated_cycles--;
            while( cycle_type[j] == 'I' ) {
                cycle_type[j] = 'O';
                j = successor[j];
            }
        }
    }

    // Next, count all nodes outside cycles
    for( int i = 1; i <= n; ++i ) {
        outside_cycles += cycle_type[i] == 'N';
        leaves += !has_predecessor[i];
    }
            
    printf( "%d %d\n", leaves + isolated_cycles, outside_cycles + cycles );
}

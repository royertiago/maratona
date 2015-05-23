/* Problema H da etapa regional da Maratona de 2009.
 *
 * The idea behind this algorithm is that every rectangle
 * removed from the block being carved
 * can be "attached" to the positive elevation change at its right.
 * Thus, for instance, if the input contains
 *      1 2 2
 * we would have attached the rectangle right above the number 1
 * to the first number 2 (that is, that elevation change "positively").
 * The only problem is the rectangles that have nothing to the right.
 * For these, we simply add a sentinel value of the height of the block,
 * so this artificial elevation change will be attached to such rectangles.
 *
 * Therefore, every rectangle can be attached to a positive elevation change,
 * and every positive elevation change will have a rectangle attached.
 * Thus it suffices to sum all positive elevation changes
 * (including the extra artificial change at the input end).
 */
#include <stdio.h>

int h; // Height of the laser sculpture
int w; // Width of the laser sculpture

// Data kept by the solver.
int last, sum;
void reset() {
    last = h;
    sum = 0;
}
void push( int val ) {
    if( val > last )
        sum += val - last;
    last = val;
}
int solve() {
    push(h);
    return sum;
}


int main() {
    while( scanf("%d %d", &h, &w) != EOF && w != 0 ) {
        reset();
        int read;
        for( int i = 0; i < w; i++ ) {
            scanf( "%d", &read );
            push(read);
        }
        printf( "%d\n", solve() );
    }
}

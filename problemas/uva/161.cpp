/* 161.cpp
 * Problema: http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=97
 * Simulação.
 */
#include <stdio.h>

/* Note que, se escolhermos o produto de todos os ciclos,
 * encontraremos uma solução da instância.
 * O problema diz que,
 * caso demore [mais] de cinco horas para sincronizar,
 * uma mensagem de erro deve ser impressa.
 * Pode ser que a sincronia ocorra no último segundo
 * deste período, portanto o intervalo é fechado
 * e precisamos desse '+1'. */
#define MAX (5*3600+1)
bool vec[MAX];

void clear() {
    for( bool & b : vec ) b = true;
}

void apply( int period ) {
    int i = 0;
    while( i < MAX ) {
        for( int j = 0; j < period - 5 && i < MAX; j++, i++ )
            ;
        for( int j = 0; j < 5 && i < MAX; j++, i++ )
            vec[i] = false; 
        for( int j = 0; j < period && i < MAX; j++, i++ )
            vec[i] = false;
    }
}

int retrieve() {
    int i = 0;
    for( ; vec[i]; i++ )
        ;
    for( ; i < MAX; i++ )
        if( vec[i] ) return i;
    return -1;
}

int main() {
    int x, y;
    while( scanf( "%d%d", &x, &y ) && x != 0 && y != 0 ) {
        clear();
        apply( x );
        apply( y );
        while( scanf("%d", &x ) && x != 0 )
            apply( x );
        y = retrieve();
        if( y == -1 )
            printf( "Signals fail to synchronise in 5 hours\n" );
        else {
            int h = y / 3600;
            y %= 3600;
            int m = y / 60;
            int s = y % 60;
            printf( "%02d:%02d:%02d\n", h, m, s );
        }
    }
    return 0;
}

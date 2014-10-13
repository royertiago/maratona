/* he.cpp
 * Problema H da etapa nacional da Maratona de 2007.
 */
#include <stdio.h>

int main() {
    int closest_attacker;
    int current_defender;
    int A, D;
    while( scanf("%d%d", &A, &D) != EOF && A != 0 && D != 0 ) {
        scanf( "%d", &closest_attacker );
        int tmp;
        while( --A ) { // Note que o pré-incremento é necessário.
            scanf( "%d", &tmp );
            closest_attacker = tmp < closest_attacker ? tmp : closest_attacker;
        }
        int ahead_count = 0;
        while( D-- ) {
            scanf( "%d", &current_defender );
            if( current_defender <= closest_attacker )
                ahead_count++;
        }
        printf( ahead_count < 2 ? "Y\n" : "N\n" );
    }
    return 0;
}

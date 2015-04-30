#include <stdio.h>

int main() {
    int N;
    while( scanf( "%d", &N ) != EOF && N != 0 ) {
        double peso_total = 0.0, soma = 0.0, peso, nota;
        while( --N ) {
            scanf( "%lf %lf", &nota, &peso );
            soma += nota * peso;
            peso_total += peso;
        }
        scanf( "%lf", &nota );
        peso = 1 - peso_total;
        soma += nota * peso;
        if( soma >= 5.0 )
            printf( "aprovado\n" );
        else
            printf( "volte no exame\n" );
    }
}

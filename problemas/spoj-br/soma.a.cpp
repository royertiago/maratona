/* soma.a.cpp
 * Problema http://br.spoj.com/problems/SOMA/
 */
#include <stdio.h>

int main() {
    int soma = 0, atual;
    scanf( "%d", &atual ); // Descartar o primeiro valor
    while( scanf( "%d", &atual ) != EOF )
        soma += atual;
    printf( "%i\n", soma );
    return 0;
}

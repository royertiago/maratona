/* Problema: http://br.spoj.com/problems/FATORIAL/
 *
 * A ideia é manter, num buffer, os dígitos menos significativos
 * não nulos de n!.
 * Por exemplo, para n = 5, armazenaremos 12 (pois n! = 120).
 *
 * Para obter os últimos dígitos de (n+1)! a partir dos últimos digitos de n!,
 * bastaria multiplicá-los por (n+1);
 * entretanto, eventualmente,
 * a quantidade de dígitos não-nulos
 * passará a ser maior do que o representável num inteiro.
 *
 * Portanto, precisamos apenas os k últimos dígitos.
 * (Usaremos dois truques para minimizar a necessidade de armazenamento:
 * primeiro, removeremos todos os múltiplos de 10 antes de múltiplicar por n+1;
 * segundo, usaremos o fato de que multiplicar por 5 é mesmo que multiplicar por 10
 * e depois dividir por 2 para tirar todos os fatores 5 do número n+1.)
 *
 * Quão grande k precisa ser?
 * A maior potência de 5 menor que 10^6 é 5^8, portanto,
 * manter os últimos 8 dígitos é suficiente.
 */
#include <stdio.h>

int cache[(int) 1e6+1];
int largest_cached = 1;

int solve( int input ) {
    if( largest_cached >= input )
        return cache[input] % 10;

    long long d = cache[largest_cached];
    for( int i = largest_cached + 1; i <= input; i++ ) {
        long long  j = i;
        while( j % 10 == 0 )
            j /= 10;

        while( j % 5 == 0 ) {
            d /= 2;
            j /= 5;
        }

        cache[i] = d = (d * j) % (long long) 1e8;
    }
    largest_cached = input;
    return d % 10;
}

int main() {
    cache[0] = cache[1] = 1;
    int n, i = 1;
    while( scanf( "%d", &n ) != EOF ) {
        printf( "Instancia %d\n%d\n\n", i++, solve(n) );
    }
    return 0;
}

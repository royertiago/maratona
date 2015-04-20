/* Problema G da seletiva doméstica da UDESC de 2015.
 */
#include <stdio.h>

int P, Q, A, N;
int respostas[10]; // O que um candidato preencheu em dada questão.
int pontos( int gabarito ) {
    int resposta = -1;
    for( int i = 0; i < A; i++ )
        if( respostas[i] <= 128 ) {
            if( resposta != -1 )
                return -1;
            else
                resposta = i;
        }
    if( resposta == -1 ) return 0;
    if( resposta == gabarito ) return 2;
    return -1;
}

int main() {
    char gabarito[100];
    scanf( "%d", &P );
    for( int prova = 1; prova <= P; prova++ ) {
        printf( "Prova #%d\n", prova );
        scanf( "%d %d %d", &Q, &A, &N );
        for( int i = 0; i < Q; i++ )
            scanf( " %c", &gabarito[i] );

        for( int candidato = 1; candidato <= N; candidato++ ) {
            int soma = 0; // Soma é 2*pontos.
            for( int i = 0; i < Q; i++ ) {
                for( int j = 0; j < A; j++ )
                    scanf( "%d", &respostas[j] );
                soma += pontos( gabarito[i] - 'a' );
            }
            /* O criador do exercício teve a "brilhante" ideia
             * de usar vírgula como separador de decimais,
             * ao invés de usar o ponto que já está embutido na linguagem.
             */
            int dec = (soma % 2) != 0 ? 5 : 0;
            const char * sign = soma >= 0 ? "" : "-";
            const char * resultado = soma >= Q ? "Aprovado" : "Reprovado";
            soma = (soma > 0 ? soma : -soma);
            printf( "Candidato #%i: %s%i,%i %s\n", candidato,
                sign, soma / 2, dec, resultado );
        }
        printf( "\n" );
    }
    return 0;
}

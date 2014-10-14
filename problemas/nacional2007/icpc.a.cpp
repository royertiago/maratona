/* icpc.a.cpp
 * Problema I da etapa nacional da Maratona de 2007.
 *
 * Este arquivo resolve o problema impondo uma série de restrições lineares
 * aos valores mínimo e máximo de penalidade.
 */
#include <stdio.h>
#include <algorithm>

struct team {
    int wa, acc, time; // WrongAnswers, Accepted answers, sum of correct times
    bool operator<( team t ) const { // Se esta vem antes da outra na colocação
        if( acc != t.acc ) return acc > t.acc;
        return wa * 20 + time < t.wa * 20 + t.time;
    }
    bool operator==( team t ) const { // Se estamos empatados
        return acc == t.acc && wa * 20 + time == t.wa * 20 + t.time;
    }
} teams[100];

int T, P;
int min_penalty, max_penalty;

#define MAX_PENALTY (10 * 300 + 1)
/* Explica-se: dadas duas equipes quaisquer, a única coisa que importa para
 * definir as penalidades é a diferença entre os tempos (team::time) e entre
 * quantidade de respostas erradas (team::wa). A diferença máxima entre os
 * tempos é 10 * 300 (pois existem 10 problemas e o tempo máximo para cada
 * um é 300), enquanto que a diferença entre a quantidade de erros é,
 * no mínimo, 1. Pela conta abaixo, o valor máximo em que a penalidade
 * ainda afeta a ordem entre as equipes é 10 * 300. MAX_PENALTY é apenas
 * um sentinela para este valor. */

int min( int i, int j ) { return i < j ? i : j; }
int max( int i, int j ) { return i > j ? i : j; }

int main() {
    while( scanf("%d%d", &T, &P) != EOF && T != 0 ) {
        for( int i = 0; i < T; i++ ) {
            teams[i] = {0, 0, 0};
            for( int j = 0; j < P; j++ ) {
                int A, S = -1;
                /* Existe um erro no juiz. O enunciado do problema diz que
                 * 1 <= S <= 300, entretanto existem casos de teste em que
                 * S == 0. */
                scanf( "%d/%d", &A, &S );
                if( S != -1 ) {
                    A--;
                    teams[i].acc++;
                    teams[i].wa += A;
                    teams[i].time += S;
                }
            }
        }

        min_penalty = 1;
        max_penalty = MAX_PENALTY;

        std::sort( teams, teams+T );

        for( int i = 0; i < T-1; ++i ) {
            if( teams[i].acc != teams[i+1].acc ) continue;
            if( teams[i].wa == teams[i+1].wa ) continue;
            /* Como a quantidade de Wrong Answers é a mesma, a penalidade 
             * não importa. */
            if( teams[i] == teams[i+1] ) {
                min_penalty = max_penalty = 20;
                break;
                /* Neste caso, como as equipes estão empatadas e uma delas
                 * teve Wrong Answers a mais que a outra, qualquer mudança
                 * na penalidade irá desempatá-las. */
            }
            /* Agora, temos uma inequação linear para resolver. Chame j = i+1.
             * Pelo critério imposto acima, teams[i] < teams[j], isto é,
             *  i.wa * penalty + i.time < j.wa * penalty + j.time */
            if( teams[i].wa > teams[i+1].wa ) {
                /* Vamos aumentar p (penalty) o máximo possível.
                 *  (i.wa - j.wa) * p < j.time - i.time
                 *                  p < (j.time - i.time)/(i.wa - j.wa)
                 * Arredondando a quantia do lado direito para cima, obtemos
                 * um valor v limite para p; p < v, ou seja, p <= v-1. */
                int p = (teams[i+1].time - teams[i].time + 
                         teams[i].wa - teams[i+1].wa - 1) /
                        (teams[i].wa - teams[i+1].wa);
                max_penalty = min( p-1, max_penalty );
            } else {
                /* Vamos reduzir P o máximo possível.
                 *  p > (j.time - i.time)/(i.wa - j.wa)
                 * Agora temos que arredondar a mesma quantia para baixo.
                 * Aqui também temos p > v, isto é, p >= v+1. */
                int p = (teams[i].time - teams[i+1].time) /
                        (teams[i+1].wa - teams[i].wa);
                min_penalty = max( p+1, min_penalty );
            }
        }
        printf( max_penalty == MAX_PENALTY ? "%d *\n" : "%d %d\n", min_penalty, max_penalty );
    }
}

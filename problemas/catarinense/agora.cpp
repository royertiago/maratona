#include <algorithm>
#include <stdio.h>

/* Este problema é parecido com o exemplo de programação dinâmica
 * que o livro do Cormen dá.
 * De fato, o nome "senhor Rod" é uma referência àquela seção,
 * entitulada "Rod cutting."
 */

struct corte {
    int tamanho;
    int preco;
};

/* pd[i] é o maior lucro que conseguimos obter com um rolo de tamanho i cm.
 */
int pd[20001];
corte cortes[200];
int num_cortes;
int tam_rolo;

int solve() {
    pd[0] = 0;
    for( int i = 1; i <= tam_rolo; i++ ) {
        pd[i] = pd[i-1];
        for( int j = 0; j < num_cortes; j++ )
            if( cortes[j].tamanho <= i )
                pd[i] = std::max( pd[i], pd[i - cortes[j].tamanho] + cortes[j].preco );
    }
    return pd[tam_rolo];
}

int main() {
    while( scanf("%d %d", &tam_rolo, &num_cortes) != EOF 
        && num_cortes != 0 && tam_rolo != 0 )
    {
        tam_rolo *= 100; // tamanho do rolo é em centímetros
        for( int i = 0; i < num_cortes; i++ )
            scanf( "%d %d", &cortes[i].tamanho, &cortes[i].preco );
        printf( "%.2f\n", solve()/100.0 );
    }
    return 0;
}

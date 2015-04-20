/* Problema E da seletiva doméstica da UDESC de 2015.
 *
 * Complexidade: n^3
 *
 * Imporemos uma restrição no local em que colocaremos a tigela:
 * a borda dela tem que ficar em cima de ao menos dois mosquitos,
 * exceto no caso extremo de que a solução é apenas um mosquito.
 *
 * Afirmação: esta restrição não reduz a quantidade máxima de mosquitos.
 * Demonstração: dada uma tigelada que maximiza a quantidade de
 * mosquitos mortos, podemos deslocar "levemente" a tigela para baixo
 * até que a borda toque em algum mosquito; e então gire a tigela
 * ao redor deste mosquito até encontrar outro.
 * Como existem ao menos dois mosquitos dentro da tigela,
 * este procedimento transforma qualquer solução numa solução que satisfaz
 * à esta restrição.
 *
 * Agora, existe um número finito de "tigeladas" que satisfaz à esta restrição;
 * mais precisamente, no máximo duas para cada par de mosquitos.
 * São O(n^2) possíveis tigeladas.
 *
 * (Dados dois mosquitos x e y, o conjunto dos pontos z tais que
 * um círculo centrado em z de raio r toca o mosquito x
 * (ou y, respectivamente) forma um círculo de raio r centrado em x
 * (ou y, respectivamente), portanto temos uma interseção de círculos.
 * Dois círculos intersectam-se em, no máximo, dois pontos.)
 *
 * Percorreremos os pares de mosquitos, calcularemos os centros,
 * e computaremos a quantidade de mosquitos pegos por cada centro
 * varrendo todos os mosquitos novamente.
 */

#include <stdio.h>
#include <utility> // std::pair
#include <cmath>
#include <algorithm>

double radius; // Raio da tigela.

struct Point {
    double x, y;
    /* Retorna o ponto, normalizado. */
    Point normalized() const;
};

double d( Point x, Point y ) {
    return std::hypot( x.x - y.x, x.y - y.y );
}
Point operator+( Point x, Point y ) {
    return Point{x.x + y.x, x.y + y.y};
}
Point operator-( Point x, Point y ) {
    return Point{x.x - y.x, x.y - y.y};
}
Point operator/( Point x, double z ) {
    return Point{x.x/z, x.y/z};
}
Point operator*( Point x, double z ) {
    return Point{x.x*z, x.y*z};
}

Point Point::normalized() const {
    return *this / d(*this, Point{0,0});
}

/* Retorna os dois possíveis centros de cículos
 * que cruzam os dois pontos, tendo raio ::radius.
 */
std::pair<Point, Point> circle_center( Point x, Point y ) {
    Point z = (x + y)/2;
    Point vec = x - y;
    if( d(vec, Point{0, 0}) < 1e-7 ) {
        /* Caso extremo: os dois pontos estão um quase em cima do outro.
         * O enunciado do problema disse para assumir que a resposta não se altera
         * caso o diâmetro do círculo aumentar em 1e-5,
         * portanto, qualquer círculo que envolva x envolverá, também, y.
         *
         * Retornaremos o par (x, y) para forçar o laço principal a lidar com
         * o caso de darmos uma tigelada em cima de um desses círculos.
         */
        return std::make_pair(x, y);
    }
    Point orth{vec.y, -vec.x};
    orth = orth.normalized();

    /* A reta que passa pelos centros dos círculos
     * é ortogonal à reta que passa por x e y.
     * z é o ponto de encontro. d(x, z) == d(x, y)/2,
     * e a distância entre os dois centros satizfaz relação semelhante.
     * Portanto, x, z e um centro formam um triângulo retângulo,
     * de catetos a e b e hipotenusa c.
     *
     * orth é um vetor normalizado ortogonal a vec;
     * vec aponta na mesma direção da reta que passa por x e y,
     * e orth aponta na mesma direção da reta que passa pelos dois centros.
     */
    double a = d(x, y)/2;
    double c = radius;
    double b = std::sqrt( c*c - a*a );

    return std::make_pair( z + orth*b, z - orth*b );
}

int point_count;
Point list[32];

/* Retorna o máximo de mosquitos que podem ser mortos
 * caso o centro da tigela esteja em c. */
int max_centered( Point c ) {
    double r = radius + 1e-6; // Tolerância dada pelo problema.
    int k = 0;
    for( int i = 0; i < point_count; i++ )
        k += d(list[i], c) <= r;
    return k;
}

int solve() {
    /* Há ainda um caso extremo a considerar: caso todos os pontos
     * fiquem longe demais. Neste caso (cuja resposta é 1)
     * sempre cairemos dentro daquele if interno,
     * e devolveremos o valor inicial de "max".
     * Portanto, basta escolher 1 para o valor inicial de max.
     */
    int max = 1;
    for( int i = 0; i < point_count; i++ )
        for( int j = i+1; j < point_count; j++ ) {
            if( d(list[i], list[j]) > 2*radius )
                continue; // Muito longe, não forma círculo.

            auto pair = circle_center(list[i], list[j]);
            max = std::max(max, max_centered(pair.first));
            max = std::max(max, max_centered(pair.second));
        }

    return max;
}

int main() {
    int t;
    scanf( "%d", &t );
    while( t-- ) {
        scanf( "%d %lf", &point_count, &radius );
        radius /= 2;
        for( int i = 0; i < point_count; i++ )
            scanf( "%lf %lf", &list[i].x, &list[i].y );

        printf( "%d\n", solve() );
    }
    return 0;
}

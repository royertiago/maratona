/* Problema B da seletiva doméstica da UDESC de 2015.
 */
#include <stdio.h>

/* Máximo de dígitos. */
#define DMAX 4

char grid[4*DMAX + 5][4*DMAX + 5 + 1];

/* xvalue é o valor que ficará na horizontal,
 * yvalue é o valor que ficará na vertical.
 *
 * xdigits é a quantidade de dígitos de xvalue,
 * xdigit são seus dígitos.
 *
 * ydigits/ydigit é o mesmo, mas para yvalue.
 */
int xvalue, yvalue;
int xdigits, ydigits;
int xdigit[DMAX], ydigit[DMAX];

/* Representa os dígitos que aparecerão no "grid interno".
 * lower_digit[i][j] == ydigit[i] * xdigit[j] % 10;
 * upper_digit[i][j] == ydigit[i] * xdigit[j] / 10.
 */
int upper_digit[DMAX][DMAX];
int lower_digit[DMAX][DMAX];

/* Limpa o vetor grid (com espaços - ' ') e constrói a moldura ao redor.
 */
void clear_grid() {
    /* O C armazena os vetores em formato "row-major order";
     * isto é, as linhas estão armazenadas contiguamente.
     * Portanto, &grid[4][0] é o endereço da quinta linha da matriz.
     *
     * Como xdigits representa o valor da horizontal,
     * teremos de usar ele para nos referirmos aos valores da última dimensão,
     * não da primeira.
     */
    for( int i = 0; i < 4*ydigits + 5; i++ ) {
        for( int j = 0; j < 4*xdigits + 5; j++ )
            grid[i][j] = ' ';
        grid[i][4*xdigits + 5] = '\0';
    }

    for( int i = 0; i < 4*ydigits + 5; i++ )
        grid[i][0] = grid[i][4*xdigits + 4] = '|';

    for( int j = 0; j < 4*xdigits + 5; j++ )
        grid[0][j] = grid[4*ydigits + 4][j] = '-';

    grid[0][0] = grid[0][4*xdigits + 4] = grid[4*ydigits + 4][0]
        = grid[4*ydigits + 4][4*xdigits + 4] = '+';
}

/* Pinta o quadrado da linha i, coluna j no grid.
 * Assume que upper_digit e lower_digit estão computados.
 */
void print_grid( int i, int j ) {
    int xshift = 4*j + 2;
    int yshift = 4*i + 2;
    for( int y = 0; y <= 4; y++ )
        grid[y + yshift][xshift] = grid[y + yshift][xshift + 4] = '|';
    for( int x = 0; x <= 4; x++ )
        grid[yshift][x + xshift] = grid[yshift + 4][x + xshift] = '-';
    for( int d = 0; d <= 4; d++ )
        grid[yshift + 4 - d][xshift + d] = '/';

    grid[yshift][xshift] = grid[yshift + 4][xshift] = grid[yshift][xshift + 4]
        = grid[yshift + 4][xshift + 4] = '+';
    grid[yshift+1][xshift+1] = upper_digit[i][j] + '0';
    grid[yshift+3][xshift+3] = lower_digit[i][j] + '0';
}

int gambiarra_log10( int i ) {
    if( i < 10 )
        return 1;
    if( i < 100 )
        return 2;
    if( i < 1000 )
        return 3;
    return 4;
}

void compute_digits() {
    xdigits = gambiarra_log10(xvalue);
    ydigits = gambiarra_log10(yvalue);
    for( int v = xvalue, k = xdigits-1; v > 0; v /= 10, k-- )
        xdigit[k] = v % 10;
    for( int v = yvalue, k = ydigits-1; v > 0; v /= 10, k-- )
        ydigit[k] = v % 10;

    for( int i = 0; i < ydigits; i++ )
        for( int j = 0; j < xdigits; j++ ) {
            lower_digit[i][j] = ydigit[i] * xdigit[j] % 10;
            upper_digit[i][j] = ydigit[i] * xdigit[j] / 10;
        }
}

void write_numbers() {
    for( int j = 0; j < xdigits; j++ )
        grid[1][4 * j + 4] = xdigit[j] + '0';
    for( int i = 0; i < ydigits; i++ )
        grid[4 * i + 4][4 * xdigits + 3] = ydigit[i] + '0';

    int prod = xvalue * yvalue;
    for( int j = xdigits; j > 0; j-- ) {
        if( prod == 0 )
            return;
        grid[4*ydigits + 3][4 * j - 1] = prod % 10 + '0';
        if( prod > 10 )
            grid[4*ydigits + 3][4 * j - 3] = '/';
        prod /= 10;
    }
    for( int i = ydigits; i > 0; i-- ) {
        if( prod == 0 )
            return;
        grid[4 * i + 1][1] = prod % 10 + '0';
        if( prod > 10 )
            grid[4 * i - 1][1] = '/';
        prod /= 10;
    }
}

int main() {
    while( scanf("%d %d", &xvalue, &yvalue) == 2 && xvalue != 0 && yvalue != 0 ) {
        compute_digits();
        clear_grid();
        write_numbers();
        for( int i = 0; i < ydigits; i++ )
            for( int j = 0; j < xdigits; j++ )
                print_grid( i, j );
        for( int i = 0; i <= 4 * ydigits + 4; i++ )
            printf( "%s\n", &grid[i][0] );
    }
    return 0;
}

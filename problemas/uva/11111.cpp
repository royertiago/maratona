/* 11111.cpp
 * Problema: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=23&page=show_problem&problem=2052
 */
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

/* Convenção: entrada termina quando m for zero. */
bool solve( const int * m ) {
    static vector<int> capacity( 1024 );
    static vector<int> size( 1024 );
    /* Usaremos duas pilhas; empilharemos as bonecas que estamos analisando,
     * no momento, retiramos as que sabemos que estão corretamente aninhadas.
     * size é o tamanho do brinquedo; é usado para garantir aninhamento.
     * capacity é a capacidade; é atualizada a cada nova inserção e deve
     *  ser sempre maior ou igual a um. */

    capacity.clear();
    size.clear();

    capacity.push_back( 0 );
    size.push_back( 0 ); // Sentinelas, para eliminar if's

    while( *m != 0 ) {
        if( *m < 0 ) { // empilhar
            capacity.back() += *m;
            size.push_back( -*m );
            capacity.push_back( -*m );
        } 
        else { // desempilhar
            if( *m != size.back() || capacity.back() <= 0 )
                return false;
            size.pop_back();
            capacity.pop_back();
        }
        ++m;
    }
    return size.size() == 1;
}

int main() {
    string str;
    vector<int> v( 1024 );
    while( getline( cin, str ) ) {
        istringstream is( str );
        int i;
        v.clear();
        while( is >> i )
            v.push_back( i );
        v.push_back( 0 );
        printf( "%s\n", solve( &v[0] ) ? ":-) Matrioshka!" : ":-( Try again." );
    }
    return 0;
}

/* 10420.cpp
 * Problema: http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1361
 *
 * std::map< std::string, unsigned >.
 */
#include <iostream>
#include <string>
#include <map>

int main() {
    int n;
    std::cin >> n;
    std::map< std::string, unsigned > count;
    std::string country;
    while( n-- ) {
        std::cin >> country;
        std::cin.ignore( 75, '\n' );
        // O problema assume que as linhas possuem, no máximo, 75 caracteres.
        count[country]++;
    }
    for( auto pair : count )
        std::cout << pair.first << ' ' << pair.second << '\n';
    return 0;
}

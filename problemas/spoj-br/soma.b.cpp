/* soma.a.cpp
 * Problema http://br.spoj.com/problems/SOMA/
 */
#include <iostream>

int main() {
    int soma = 0, atual;
    std::cin >> atual; // Descartar o primeiro valor
    while( std::cin >> atual )
        soma += atual;
    std::cout << soma << std::endl;
    return 0;
}

/* f91.c.cpp
 * Problema http://br.spoj.com/problems/F91/
 * Esta solução usa iostream, e estoura o tempo limite.
 */
#include <iostream>

int f91( int n ) {
    if( n < 101 )
        return 91;

    return n - 10;
}

int main() {
    int n;
    while( std::cin >> n && n != 0 )
        std::cout << "f91(" << n << ") = " << f91(n) << "\n";
    return 0;
}

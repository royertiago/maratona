/* 1244.cpp
 * Problema: https://www.urionlinejudge.com.br/judge/en/problems/view/1244
 */

#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

int main() {
    string buf;
    int i;
    cin >> i;
    cin.get();
    while( i-- ) {
        vector<string> vec;
        getline( cin, buf );
        istringstream in( buf );
        string tmp;
        while( in >> tmp ) vec.push_back( tmp );
        stable_sort( vec.begin(), vec.end(), []( const string& a, const string& b ){ return a.size() > b.size(); } );
        unsigned j;
        for( j = 0; j < vec.size() - 1; ++j )
            cout << vec[j] << ' ';
        cout << vec[j] << '\n';
    }
    return 0;
}

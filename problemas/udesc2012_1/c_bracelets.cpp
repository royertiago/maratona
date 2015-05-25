/* Problema C da 1ª seletiva da UDESC de 2012.
 *
 * Longest common subsequence.
 *
 * The function "solve" below will solve the problem for a given bracelet orientation.
 * Note that, altough there are four possible orientations,
 * if both bracelets are inverted, their greatest "activation sequence"
 * is the same, just also reversed,
 * so there are two "really" different orientations.
 * Henceforth, we assume some orientation was fixed.
 *
 * Given a greatest activation sequence,
 * we may chose a starting point in one of the bracelets
 * and see where are the corresponding starting point in the other bracelet.
 * Linearize both bracelets; the activation sequence becomes
 * a common subsequence of the strings that represent the bracelet.
 * This subsequence must be the (or a) longest,
 * because, otherwise, we could generate a greater activation sequence
 * using a longer common subsequence.
 * Thus, the greatest activation sequence has the same size
 * of some longest common subsequence of some linearization of both bracelets.
 *
 * Observe that we have choosen the starting point in the first bracelet.
 * In the algorithm, we will make the choice of starting the first bracelet
 * exactly where its string start;
 * this way, the input string is exactly the chosen bracelet linearization.
 * So, we just need to iterate through all the linearizations of the second bracelet.
 * They are exactly all the circular permutations of the second string.
 *
 * Finally, note that any common subsequence of any linearization of both bracelets
 * yields a valid activation sequence --- just maybe smaller ones.
 *
 * Conclusion: when searching through all longest common subsequences
 * between the input string and all the circular permutations of the second string,
 * the greatest value we encounter is exactly the size
 * of the greatest activation sequence.
 *
 * Complexity: O(n^3).
 */
#include <algorithm>
#include <iostream>
#include <string>

/* Longest Common Subsequence
 */
int lcs( const std::string& a, const std::string& b ) {
    /* lcs[i][j] is the size of the greatest common subsequence
     * of the sequences a[0, ..., i] and b[0, ..., j].
     */
    static int lcs[100][100];
    lcs[0][0] = a[0] == b[0];
    for( int j = 1; j < b.size(); j++ )
        lcs[0][j] = std::max<int>( a[0] == b[j], lcs[0][j-1] );
    /* I've used std::max<int> instead of just std::max
     * because the first argument is of type bool,
     * and the last argument is of type int&.
     * The deducted arguments conflict.
     */

    for( int i = 1; i < a.size(); i++ ) {
        lcs[i][0] = std::max<int>( a[i] == b[0], lcs[i-1][0] );
        for( int j = 1; j < b.size(); j++ )
            lcs[i][j] = std::max<int>( std::max<int>(
                (a[i] == b[j]) + lcs[i-1][j-1],
                lcs[i][j-1]),
                lcs[i-1][j]
            );
    }
    return lcs[a.size() - 1][b.size() - 1];
}

int solve( std::string a, std::string b ) {
    int max = 0;
    for( int i = 0; i < a.size(); i++ ) {
        std::string str = a.substr( i ) + a.substr( 0, i );
        max = std::max( max, lcs(str, b) );
    }
    return 2*max;
}

int main() {
    std::string a, b;
    while( std::cin >> a >> b )
        std::cout << std::max(
            solve( a, b ),
            solve( a, std::string(b.rbegin(), b.rend()) )
        )
        << std::endl;
}

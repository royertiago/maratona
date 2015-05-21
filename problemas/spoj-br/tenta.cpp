/* tenta.cpp
 * Problem: http://br.spoj.com/problems/TENTA/
 *
 * Implementation of std::next_permutation.
 *
 *
 * Implementing the linear function function below directly is tough;
 * it is best to start with a recursive definition.
 * We will make the simplifying assumption that,
 * when next_permutation would return false,
 * the permutation is left untouched.
 *
 * Let's assume the signature next( int b, int e )
 * to mean permute the global vector 'a' in the range [b, e].
 *
 * The base of the recursion is when b == e;
 * that is, the range contains only a single element.
 * Simply return false there.
 *
 * Assume b < e. Since we are going for the lexicographically next permutation,
 * we should modify the position b only if there is no more options.
 * So, we first run the algorithm in next(b+1, e) and see its return value.
 * If it is true, return true;
 * the recursive call already changed the vector to the next permutation.
 *
 * But if next(b+1, e) == false, this means there is no next permutation
 * in the subrange [b+1, e].
 * This can only happen if the entire range [b+1, e] is sorted backwards.
 *
 * If a[b] >= a[b+1], then the range [b, e] is sorted backwards.
 * So, there is no next permutation for our range either;
 * thus, return false.
 *
 * If not (that is, a[b] < a[b+1]), there is a next permutation.
 * We must construct it.
 * Since we are going for the lexicographically next permutation,
 * we will strive for substituting a[b] for the least possible value
 * that is greater than a[b].
 * Swap this value and a[b], then sort the range [b+1, e].
 * This will give the next permutation,
 * since we exausted all permutations with a[b] in the beginning,
 * we have chosen the first element possible as the new a[b],
 * and the range [b+1, e] is sorted.
 *
 * However, we may take advantage over the fact that [b+1, e]
 * is reversely sorted to make a linear-time sorting.
 * Let i be the last index such that a[i] > a[b].
 * Since a[b] < a[b+1], i > b.
 * And, since [b+1, e] is sorted in descending order,
 * a[i] is, in fact, the smallest value in [b+1, e] greater than a[b],
 * so a[i] is the value we must swap for a[b].
 * And, after the swap, [b+1, e] is still in descending order:
 * any value after a[i] will be equal to or smaller than a[b]
 * since a[i] was the last value grater than a[b],
 * and every value between a[b+1] and a[i-1] will be
 * greater than or equal a[i] --- and thus greater than a[b].
 *
 * Therefore, we must simply find i, swap a[i] with a[b],
 * and reverse the range a[b+1, e].
 *
 * Then, return true.
 *
 * This algorithm may be summarized by
 * bool next( int b, int e ) {
 *     if( b == e )
 *         return false;
 *     if( next(b+1, e) )
 *         return true;
 *
 *     if( a[b] >= a[b+1] )
 *         return false;
 *
 *     int i = n - 1;
 *     while( a[i] <= a[j] )
 *         i--;
 *
 *     std::swap( a[i], a[j] );
 *     std::reverse( a + j + 1, a+n );
 * }
 *
 * Now, we will make this procedure non-recursive.
 *
 * After the fist 'return true' of this chain of recursive calls,
 * every function will simply return true, without touching the vector.
 * And between the deepest call (the first 'if')
 * and the first time we fall out of the third 'if',
 * we will do some work in the vector,
 * and begin the chain of 'return true'.
 *
 * Thus, the "workflow" is:
 * in the deepest level, return false;
 * go up some levels, returning false;
 * fail the third 'if', do some work in the vector, return true;
 * go up till the first level, always returning true.
 *
 * The important bit is the "go up some levels" part;
 * we will keep going up while the range [b, e] is in descending order.
 * This point may be found by iterating reversely from e to b;
 * we do not need recursion for that.
 *
 * And after we found this part, we will modify the vector,
 * and the 'return true' will propagate to the first call.
 * We also do not need recursion for that.
 *
 * So, we may find the first point where we stop propagating the 'return false',
 * do the work in the vector, and return true
 * (that would have been propagated until the first call).
 *
 * The result is show below.
 */
#include <stdio.h>
#include <algorithm>

int a[8];
int n;

/* Either permutes the vector a to the next permutation and returns true,
 * or left a untouched and returns false.
 */
bool next() {
    if( n == 1 )
        return false;

    // First, locate where we would stop "going up" in the recursive version.
    int b = n - 2;
    for( ; b >= 0; b-- )
        if( a[b] < a[b + 1] )
            break;

    // Special case: we went all the way up to the first call.
    if( b == -1 )
        return false;

    // note that a[b+1, ..., n-1] is sorted by descending order.

    int i = n - 1;
    while( a[i] <= a[b] )
        i--;

    // i contains the first element smaller than b.
    std::swap( a[i], a[b] );
    std::reverse( a + b + 1, a+n );
    return true;
}

int main() {
    const char * delim = "";
    while( scanf( "%d", &n ) != EOF, n != 0 ) {
        for( int i = 0; i < n; i++ )
            scanf( "%d", &a[i] );

        printf( delim );
        delim = "\n";

        std::sort( a, a+n );
        do {
            const char * delim = "";
            for( int i = 0; i < n; i++ ) {
                printf( "%s%d", delim, a[i] );
                delim = " ";
            }
            printf( "\n" );
        } while( next() );
    }

    return 0;
}

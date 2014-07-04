/* expres11.cpp
 * Problema http://br.spoj.com/problems/EXPRES11/
 */
#include <stdio.h>

// true caso a entrada esteja bem definida, false caso contrário.
bool analyse( const char* input ) {
    static char stack[100000];
    int top = -1;
    while( *input != '\0' ) {
        switch( *input ) {
            case '(':
            case '[':
            case '{':
                stack[++top] = *input;
                break;
            case ')':
                if( top == -1 || stack[top--] != '(' )
                    return false;
                break;
            case ']':
                if( top == -1 || stack[top--] != '[' )
                    return false;
                break;
            default: // case '}'
                if( top == -1 || stack[top--] != '{' )
                    return false;
        }

        ++input;
    } // fim while
    return top == -1;
}

int main() {
    char input[100001];
    int instances;
    scanf( "%d\n", &instances );
    for( int i = 0; i < instances; ++i ) {
        scanf( "%s\n", input );
        if( analyse( input ) )
            printf( "S\n" );
        else
            printf( "N\n" );
    }
    return 0;
}

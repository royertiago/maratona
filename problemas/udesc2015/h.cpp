#include <stdio.h>

int main() {
    int C, A, B;
    while( scanf( "%d %d %d", &C, &A, &B ) != EOF && C != 0 )
        printf( "%d %d\n", C * A, C * B );
    return 0;
}

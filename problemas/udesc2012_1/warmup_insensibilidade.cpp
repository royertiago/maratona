#include <stdio.h>

int main() {
    int obj;
    while( scanf("%d", &obj) != EOF && obj != 0 ) {
        int sum = 0;
        while( obj-- ) {
            int x1, x2, y1, y2;
            scanf( "%d %d %d %d", &x1, &y1, &x2, &y2 );
            sum += (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
        }
        printf( "%d\n", sum );
    }
    return 0;
}

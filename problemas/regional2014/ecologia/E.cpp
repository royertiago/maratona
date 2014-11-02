/* E.cpp
 * Problema da etapa regional da Maratona de 2014.
 *
 * Força bruta.
 *
 * Mirror: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4660
 */
#include <stdio.h>
#include <set>
#include <algorithm>
#include <utility>
#include <vector>

struct coord { // coordinate
    int x; int y;
    static coord neighbourhood[4];
    void n() const { // neighbours
        neighbourhood[0] = {x, y+1};
        neighbourhood[1] = {x, y-1};
        neighbourhood[2] = {x+1, y};
        neighbourhood[3] = {x-1, y};
    }
    bool operator<( coord c ) const {
        if( x != c.x ) return x < c.x;
        return y < c.y;
    }
    bool operator==( coord c ) const {
        return x == c.x && y == c.y;
    }
};
coord coord::neighbourhood[4];

struct seq { // Sequence of contiguous coordinates
    std::vector<coord> c;

    bool operator<( seq s ) const {
        return c < s.c;
    }
    // Modify the vector so that all coordinates are positive.
    void adjust() {
        int xmin = c[0].x, ymin = c[0].y;
        for( unsigned i = 1; i < c.size(); ++i ) {
            xmin = std::min( xmin, c[i].x );
            ymin = std::min( ymin, c[i].y );
        }
        for( unsigned i = 0; i < c.size(); ++i ) {
            c[i].x -= xmin;
            c[i].y -= ymin;
        }
    }
    bool append( coord next ) {
        auto it = std::lower_bound( c.begin(), c.end(), next );
        if( *it == next ) return false;
        c.insert( it, next );
        return true;
    }
    coord max() const {
        coord d = c[0];
        for( unsigned i = 1; i < c.size(); ++i ) {
            d.x = std::max( d.x, c[i].x );
            d.y = std::max( d.y, c[i].y );
        }
        return d;
    }
    void print() const {
        static char p[10][11];
        coord d = max();
        for( int i = 0; i <= d.x; ++i ) {
            for( int j = 0; j <= d.y; ++j )
                p[i][j] = ' ';
            p[i][d.y+1] = '\0';
        }
        for( coord e : c )
            p[e.x][e.y] = 'X';
        for( int i = 0; i <= d.x; ++i )
            printf( "%s\n", p[i] );
        printf( "\n" );

    }
};

std::set<seq> sequences[10];
int N, M;
int trees[50][50];

void generate_sequences() {
    sequences[0] = {seq{{{0, 0}}}};
    static int i = 1;
    for( ; i < M; ++i ) {
        for( auto s : sequences[i-1] ) {
            for( coord c : s.c ) {
                c.n();
                for( coord d : coord::neighbourhood ) {
                    seq next = s;
                    if( next.append( d ) ) {
                        next.adjust();
                        sequences[i].insert( next );
                    }
                }
            }
        }
    }
}

int solve() {
    generate_sequences();
    int best = 0;
    for( seq s : sequences[M-1] ) {
        coord m = s.max();
        for( int i = 0; i + m.x < N; ++i )
            for( int j = 0; j + m.y < N; ++j ) {
                int sum = 0;
                for( coord c : s.c )
                    sum += trees[c.x+i][c.y+j];
                best = std::max( best, sum );
            }
    }
    return best;
}

int main() {
    while( scanf( "%d %d", &N, &M ) != EOF ) {
        for( int i = 0; i < N; ++i )
            for( int j = 0; j < N; ++j )
                scanf( "%d", &trees[i][j] );
        printf( "%d\n", solve() );
    }
    return 0;
}

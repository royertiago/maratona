/* choc09.cpp
 * Problem: http://br.spoj.com/problems/CHOC09/
 *
 * Reversed dynamic programming.
 *
 * (Thorough this code, a 'play' is a number of chocolate balls we will eat.)
 */
#include <iostream>

int n, m;

#define NO_PERFECT_PLAY -1
#define TWO_PERFECT_PLAYS -2

/* play[i] is either
 * - the value of the only perfect play at round i.
 * - the constant TWO_PERFECT_PLAYS.
 * - the constant NO_PERFECT_PLAY.
 *
 * Thus, for instance, if play[8] == 3,
 * this means that we must play 3 to win.
 * In this situation, the current player win conditionally:
 * we can only win if the other player has not choosen to play 3 the last round.
 * Neverthless, if this is the starting move, we win.
 *
 * If play[9] == TWO_PERFECT_PLAYS, this means that the next player
 * has at least two winning moves in this exact state.
 * Therefore, it does not matter the play of the other player:
 * at most one of our plays can be blocked, we always have one valid perfect play.
 * We win inconditionally in this move.
 *
 * If play[10] == NO_PERFECT_PLAY, then no matter what we play,
 * we will either land in a TWO_PERFECT_PLAYS move for the next player,
 * or in a conditional winning position, but without blocking that winning move.
 * We lose inconditionally in this move.
 */
short play[(int)1e6+1];

/* If current_play is one of the elements of the play[] vector,
 * return the new option, if we add a new perfect play to that position.
 */
int add_play( int current_play, int new_play ) {
    /* We have only two cases to consider.
     * If there is no current perfect play for our next move,
     * then the only perfect play is next_play.
     *
     * Otherwise, we will have at least two perfect plays,
     * so it suffices to return TWO_PERFECT_PLAYS.
     */
    if( current_play == NO_PERFECT_PLAY )
        return new_play;
    return TWO_PERFECT_PLAYS;

    /* Notice that we are missing the case that the next play
     * is exactly the current play.
     * This causes no problem because the 'solve' algorithm below
     * never calls add_play in this situation.
     */
}

/* Return true if the first player has a perfect play.
 */
bool solve() {
    /* We will solve backwards.
     * We start by considering that there is no possible perfect play,
     * at any position.
     * Then we will consider the current play,
     * and reassign every possible perfect play above us.
     */
    for( int i = 0; i <= n; i++ )
        play[i] = NO_PERFECT_PLAY;

    for( int i = 0; i <= n; i++ )
        if( play[i] == NO_PERFECT_PLAY ) {
            /* If the current state has no perfect play,
             * any state that transitions to this state has a perfect play
             * --- namely, shifting to this position.
             */
            for( int j = 1; j <= m && i + j <= n; j++ )
                play[i+j] = add_play(play[i+j], j);
        }
        else if( play[i] == TWO_PERFECT_PLAYS )
            /* Nothing to do here.
             * Any move above us must work around this state to win,
             * so we do not change it.
             */
            continue;
        else {
            /* We have only one perfect play for this position;
             * let's say p.
             * Then the state i + p automatically gains another perfect play:
             * namely, playing p.
             */
            int p = play[i];
            if( i + p <= n )
                play[i + p] = add_play( play[i + p], p );
        }

    /* Complexity analysis:
     * Everything seems linear on n, except the first if.
     * It seems that that inner loop forces a complexity of m * n.
     * The catch is that there is very few NO_PERFECT_PLAY states.
     *
     * Note that the only point of the algorithm that generates NO_PERFECT_PLAY states
     * is the initial 'for'.
     * At each time the algorithm enters the first 'if',
     * it will clear the next m NO_PERFECT_PLAY states, changing them to
     * at least conditionally winning states.
     * Thus, we will only enter that 'if' again after it has passed m states.
     * So, we will execute the inner statement of that loop at most n times.
     *
     * Therefore, the complexity of the algorithm is linear in n.
     */
    return play[n] != NO_PERFECT_PLAY;
}

int main() {
    while( std::cin >> n >> m )
        std::cout << (solve() ? "Paula\n" : "Carlos\n");

    return 0;
}

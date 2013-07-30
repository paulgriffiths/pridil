/*
 *  game.cpp
 *  ========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of Game functionality for Prisoners' Dilemma simulation.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <string>
#include "game.h"

using namespace pridil;


/*
 *  Returns a string describing a game move.
 *
 *  Arguments:
 *    move -- a GameMove value
 *
 *  Returns:
 *    a std::string describing the supplied GameMove
 *
 *  Exceptions thrown:
 *    BadGameMove() on an unrecognized game move.
 */

std::string pridil::game_move_name(const GameMove& move) {
    std::string move_name;

    switch ( move ) {
        case coop:
            move_name = "Cooperate";
            break;

        case defect:
            move_name = "Defect";
            break;

        case coop_recip:
            move_name = "Reciprocal cooperate";
            break;

        case defect_retal:
            move_name = "Retaliatory defect";
            break;

        case coop_random:
            move_name = "Random cooperate";
            break;

        case defect_random:
            move_name = "Random defect";
            break;

        default:
            throw BadGameMove();
            break;
    }

    return move_name;
}


/*
 *  Simplifies a game move.
 *
 *  Transforms any provided move into a simple cooperate or
 *  defect move, e.g. a 'defect_retal' move will be transformed
 *  into a simple 'defect' move. Used to simplify the computation
 *  of game results.
 *
 *  Arguments:
 *    move -- a supplied GameMove
 *
 *  Returns:
 *    Another GameMove value of either 'coop' or 'defect'
 *
 *  Exceptions thrown:
 *    BadGameMove() on an unrecognized game move.
 */

GameMove pridil::simplify_game_move(const GameMove& move) {
    GameMove simplified_move;

    switch ( move ) {
        case coop:
        case coop_recip:
        case coop_random:
            simplified_move = coop;
            break;

        case defect:
        case defect_retal:
        case defect_random:
            simplified_move = defect;
            break;

        default:
            throw BadGameMove();
            break;
    }

    return simplified_move;
}


/*
 *  Calculates a game result.
 *
 *  Arguments: references to two GameInfo structures, one for
 *  each player. Only one such structure is necessarily to calculate
 *  the result, but the function stores the result for each player
 *  in their respective structure.
 *
 *  With the values specified, a cooperating Creature has a 50%
 *  chance of netting 3, and a 50% chance of losing 1, giving an
 *  expected reward of 1 and making it rational to play.
 *
 *  A defecting creature has a 50% chance of netting 5, and a 50%
 *  chance of losing 1, giving an expected reward of 2 and making
 *  it rational to play.
 *
 *  With values comparable to these, on a game-by-game basis, it is
 *  rational for each Creature to defect. On a game-by-game basis,
 *  there therefore appears to be no incentive to ever cooperate,
 *  even though the reward to each Creature if they both cooperate
 *  is 3, compared to the cost of 1 if each Creature defects. The
 *  impetus behind this simulation is to investigate whether there
 *  is a rational basis for cooperation when we move beyond a simple
 *  game-by-game analysis, and in particular when we allow each Creature
 *  to remember each other Creature it interacts with, allowing for
 *  the possibility that previous interactions with a 'nice' Creature
 *  may make it rational to cooperate if an expectation can thereby be
 *  developed that a particular Creature is likely to reciprocate
 *  (although the genetic strategies do not actually calculate
 *  probabilities, and merely react mechanically based on prior
 *  interactions).
 */

void pridil::game_result(GameInfo& own_ginfo, GameInfo& opp_ginfo) {
    static const int reward_coop = 6;
    static const int cost_to_play = 1;
    static const int cost_to_coop = 2;

    GameMove own_move = simplify_game_move(own_ginfo.own_move);
    GameMove opp_move = simplify_game_move(opp_ginfo.own_move);

    if ( own_move == coop && opp_move == coop ) {
        own_ginfo.result = opp_ginfo.result = reward_coop - cost_to_play -
                                              cost_to_coop;
    } else if ( own_move == defect && opp_move == defect ) {
        own_ginfo.result = opp_ginfo.result = -cost_to_play;
    } else if ( own_move == defect && opp_move == coop ) {
        own_ginfo.result = reward_coop - cost_to_play;
        opp_ginfo.result = -cost_to_play - cost_to_coop;
    } else if ( own_move == coop && opp_move == defect ) {
        own_ginfo.result = -cost_to_play - cost_to_coop;
        opp_ginfo.result = reward_coop - cost_to_play;
    } else {
        throw BadGameMove();
    }
}

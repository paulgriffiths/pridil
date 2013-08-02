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
 */

void pridil::game_result(GameInfo& own_ginfo, GameInfo& opp_ginfo) {
    static const int coop_benefit = 6;
    static const int play_cost = 1;
    static const int coop_cost = 2;

    static const int reward_result = coop_benefit - coop_cost - play_cost;
    static const int temptation_result = coop_benefit - play_cost;
    static const int sucker_result = -coop_cost - play_cost;
    static const int punishment_result = -play_cost;

    //  Note: getting 'own_move' from 'opp_ginfo', and vice versa, in
    //  the following lines avoids two superfluous calls to
    //  simplify_game_move(), since the opponent's move is already
    //  simplified in a GameInfo struct, but the creature's own move
    //  is not.

    const GameMove own_move = opp_ginfo.opponent_move;
    const GameMove opp_move = own_ginfo.opponent_move;

    if ( own_move == coop && opp_move == coop ) {
        own_ginfo.result = reward_result;
        opp_ginfo.result = reward_result;
    } else if ( own_move == defect && opp_move == defect ) {
        own_ginfo.result = punishment_result;
        opp_ginfo.result = punishment_result;
    } else if ( own_move == defect && opp_move == coop ) {
        own_ginfo.result = temptation_result;
        opp_ginfo.result = sucker_result;
    } else if ( own_move == coop && opp_move == defect ) {
        own_ginfo.result = sucker_result;
        opp_ginfo.result = temptation_result;
    } else {
        throw BadGameMove();
    }
}

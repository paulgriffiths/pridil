/*
 *  game.h
 *  ======
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to Game functionality for Prisoners' Dilemma simulation.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_GAME_H
#define PG_PRIDIL_GAME_H

#include <string>

#include "pridil_types.h"


/*
 *  Structure to record the result of a game, used as the basis of
 *  Creature memories of previous interactions with a given
 *  opponent.
 */

struct GameInfo {
    CreatureID id;
    GameMove own_move;
    GameMove opponent_move;
    int result;

    GameInfo(const GameInfo& gInfo) :
        id(gInfo.id), own_move(gInfo.own_move),
        opponent_move(gInfo.opponent_move), result(gInfo.result) {}
    GameInfo(const CreatureID& i, const GameMove& ow,
             const GameMove& op, const int res) :
        id(i), own_move(ow), opponent_move(op), result(res) {}
    GameInfo() : id(0), own_move(coop), opponent_move(coop), result(3) {}
};


/*
 *  Standalone game function definitions
 */

std::string game_move_name(const GameMove move);
GameMove simplify_game_move(const GameMove move);
void game_result(GameInfo& own_ginfo, GameInfo& opp_ginfo);

#endif      // PG_PRIDIL_GAME_H

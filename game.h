/*
 *  game.h
 *  ======
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to Game functionality for Prisoners' Dilemma simulation.
 *
 *  The provided functions allow for the calculation of game results,
 *  and for the simplication and naming of game moves.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_GAME_H
#define PG_PRIDIL_GAME_H

#include <string>
#include "pridil_common.h"

namespace pridil {
    std::string game_move_name(const GameMove& move);
    GameMove simplify_game_move(const GameMove& move);
    void game_result(GameInfo& own_ginfo, GameInfo& opp_ginfo);
}

#endif      // PG_PRIDIL_GAME_H

/*
 *  always_cooperate_gene.cpp
 *  =========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of AlwaysCooperateGene.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <string>
#include "../../pridil_common.h"
#include "always_cooperate_gene.h"

using namespace pridil;


/*
 *  name getter method
 */

std::string AlwaysCooperateGene::name() const {
    return std::string("always cooperate");
}

#pragma GCC diagnostic ignored "-Wunused-parameter"

/*
 *  Disable GCC unused-parameter warnings for the following function, which
 *  is virtual. The parameter is needed for this function in other gene
 *  classes, and are deliberately ignored for this where the strategy
 *  is independent of any memories of previous interactions with the
 *  opponent creature.
 */

/*  
 *  AlwaysCooperateGene, as the name suggests, always cooperates regardless
 *  of memories of previous encounters with a particular opponent.
 *  Naturally, it is the nicest gene of all.
 */

GameMove AlwaysCooperateGene::get_game_move(const CreatureID opponent) const {
    return coop;
}

#pragma GCC diagnostic pop

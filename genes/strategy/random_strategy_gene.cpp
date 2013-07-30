/*
 *  random_strategy_gene.cpp
 *  ========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of RandomStrategyGene.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <string>
#include <cstdlib>
#include "../../pridil_common.h"
#include "random_strategy_gene.h"

using namespace pridil;


/*
 *  name getter method definition
 */

std::string RandomStrategyGene::name() const {
    return std::string("random strategy");
}


#pragma GCC diagnostic ignored "-Wunused-parameter"

/*
 *  Disable GCC unused-parameter warnings for the following function, which
 *  is virtual. The parameter is needed for this function in other
 *  classes, and are deliberately ignored for these where the strategy
 *  is independent of any memories of previous interactions with the
 *  opponent creature.
 */

/*
 *  RandomStrategyGene randomly defects 50% of the time, and cooperates
 *  50% of the time, with no regard to memories of previous encounters
 *  with a particular opponent.
 */

GameMove RandomStrategyGene::get_game_move(const CreatureID opponent) const {
    return ( (rand() % 2) ? coop : defect );
}

#pragma GCC diagnostic pop

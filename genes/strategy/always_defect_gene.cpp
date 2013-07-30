/*
 *  always_defect_gene.cpp
 *  ======================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of AlwaysDefectGene.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <string>

#include "../../pridil_common.h"
#include "always_defect_gene.h"


/*
 *  name getter method definition
 */

std::string AlwaysDefectGene::name() const {
    return std::string("always defect");
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
 *  AlwaysDefectGene, as the name suggests, always defects regardless of
 *  memories of previous encounters with a particular opponent. Naturally,
 *  it is the nastiest gene of all.
 */

GameMove AlwaysDefectGene::get_game_move(const CreatureID opponent) const {
    return defect;
}

#pragma GCC diagnostic pop

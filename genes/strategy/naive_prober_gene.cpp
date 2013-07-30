/*
 *  naive_prober_gene.cpp
 *  =====================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of NaiveProberGene.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <string>
#include <cstdlib>

#include "../../pridil_common.h"
#include "naive_prober_gene.h"


/*
 *  name getter method definition
 */

std::string NaiveProberGene::name() const {
    return std::string("naive prober");
}


/*
 *  NaiveProberGene works in the same way as TitForTatGene, except on
 *  each move there is a random probability (such probability
 *  represented by the m_prob_random_defect member) of it defecting.
 *  It is therefore nastier than TitForTatGene.
 */

GameMove NaiveProberGene::get_game_move(const CreatureID opponent) const {
    GameMove my_move;

    if ( m_brain.recognize(opponent) == false ) {
        my_move = coop;
    } else {
        if ( m_brain.remember_move(opponent) == defect ) {
            my_move = defect_retal;
        } else {
            if ( ((static_cast<double> (rand())) / RAND_MAX) <
                  m_prob_random_defect ) {
                my_move = defect_random;
            } else {
                my_move = coop_recip;
            }
        }
    }
    return my_move;
}

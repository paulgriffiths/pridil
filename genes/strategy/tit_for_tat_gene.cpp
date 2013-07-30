/*
 *  tit_for_tat_gene.cpp
 *  ====================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of TitForTatGene.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <string>

#include "../../pridil_common.h"
#include "tit_for_tat_gene.h"


/*
 *  name getter method definition
 */

std::string TitForTatGene::name() const {
    return std::string("tit for tat");
}


/*
 *  TitForTatGene cooperates on its first encounter with a particular
 *  opponent, and thereafter reciprocally cooperates if that opponent
 *  cooperated during the preceding game, and defects in retaliation
 *  if that opponent defected during the preceding game.
 */

GameMove TitForTatGene::get_game_move(const CreatureID opponent) const {
    GameMove my_move;

    if ( m_brain.recognize(opponent) == false ) {
        my_move = coop;
    } else {
        if ( m_brain.remember_move(opponent) == defect ) {
            my_move = defect_retal;
        } else {
            my_move = coop_recip;
        }
    }
    return my_move;
}

/*
 *  susp_tit_for_tat_gene.cpp
 *  =========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of SuspTitForTatGene.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <string>
#include "../../pridil_common.h"
#include "susp_tit_for_tat_gene.h"

using namespace pridil;


/*
 *  name getter method definition
 */

std::string SuspTitForTatGene::name() const {
    return std::string("suspicious tit for tat");
}


/*
 *  SuspTitForTatGene works in the same way as TitForTatGene, except on
 *  its first encounter with a particular opponent, it defects rather
 *  than cooperates. SuspTitForTatGene is therefore nastier than
 *  TitForTatGene.
 */

GameMove SuspTitForTatGene::get_game_move(const CreatureID opponent) const {
    GameMove my_move;

    if ( m_brain.recognize(opponent) == false ) {
        my_move = defect;
    } else {
        if ( m_brain.remember_move(opponent) == defect ) {
            my_move = defect_retal;
        } else {
            my_move = coop_recip;
        }
    }
    return my_move;
}

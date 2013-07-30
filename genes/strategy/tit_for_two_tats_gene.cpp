/*
 *  tit_for_two_tats_gene.cpp
 *  =========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of TitForTwoTatsGene.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <string>
#include "../../pridil_common.h"
#include "tit_for_two_tats_gene.h"

using namespace pridil;


/*
 *  name getter method definition
 */

std::string TitForTwoTatsGene::name() const {
    return std::string("tit for two tats");
}


/*
 *  TitForTatGene cooperates on its first encounter with a particular
 *  opponent, and thereafter reciprocally cooperates if that opponent
 *  cooperated during the preceding game, and defects in retaliation
 *  if that opponent defected during the preceding game.
 */

/*
 *  TitForTwoTatsGene works in the same way as TitForTatGene, except it
 *  will tolerate two defections before retaliating with a defection of
 *  its own. It is therefore nicer than TitForTatGene, which can get caught
 *  in an endless cycle of mutual recriminations (e.g. with a
 *  SuspTitForTatGene).
 */

GameMove TitForTwoTatsGene::get_game_move(const CreatureID opponent) const {
    GameMove my_move;

    if ( m_brain.recognize(opponent) == false ) {
        my_move = coop;
    } else {
        unsigned int n_moves = m_brain.num_memories(opponent);

        if ( n_moves < 2 ) {
            if ( m_brain.remember_move(opponent) == coop ) {
                my_move = coop_recip;
            } else {
                my_move = coop;
            }
        } else {
            if ( m_brain.remember_move(opponent) == defect &&
                 m_brain.remember_move(opponent, 2) == defect ) {
                my_move = defect_retal;
            } else if ( m_brain.remember_move(opponent) == defect &&
                        m_brain.remember_move(opponent, 2) == coop ) {
                my_move = coop;
            } else {
                my_move = coop_recip;
            }
        }
    }
    return my_move;
}

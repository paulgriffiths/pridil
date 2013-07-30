/*
 *  dna.cpp
 *  =======
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of DNA class for Prisoners' Dilemma simulation.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <string>
#include <cstdlib>

#include "brain_complex.h"
#include "genes.h"


/*
 *  DNA class constructor
 *
 *  m_strategy_gene is a pointer, and the associated genes are created
 *  with the new operator, because we need polymorphism via a base
 *  class.
 */

DNA::DNA(const Brain& brain, const Strategy strategy) :
        m_brain(brain),
        m_strategy_gene(0) {
    switch ( strategy ) {
        case tit_for_tat:
            m_strategy_gene = new TitForTatGene(m_brain);
            break;
        case tit_for_two_tats:
            m_strategy_gene = new TitForTwoTatsGene(m_brain);
            break;
        case susp_tit_for_tat:
            m_strategy_gene = new SuspTitForTatGene(m_brain);
            break;
        case naive_prober:
            m_strategy_gene = new NaiveProberGene(m_brain);
            break;
        case random_strategy:
            m_strategy_gene = new RandomStrategyGene(m_brain);
            break;
        case always_cooperate:
            m_strategy_gene = new AlwaysCooperateGene(m_brain);
            break;
        case always_defect:
            m_strategy_gene = new AlwaysDefectGene(m_brain);
            break;
        default:
            throw UnknownStrategy();
     }
}


/*
 *  DNA destructor, deletes strategy gene
 */

DNA::~DNA() {
    delete m_strategy_gene;
}


/*
 *  Returns the name of the playing strategy contained in DNA
 */

const std::string DNA::strategy() const {
    return m_strategy_gene->name();
}


/*
 *  Returns the strategy enumeration value of the strategy gene.
 */

Strategy DNA::strategy_value() const {
    return m_strategy_gene->strategy();
}

/*
 *  Gets a game move against a particular opponent.
 *
 *  The DNA object consults its strategy gene to determine the move.
 *
 *  Arguments:
 *    opponent -- the ID of the opponent.
 *
 *  Returns:
 *    A GameMove object representing the move played.
 */

GameMove DNA::get_game_move(const CreatureID opponent) const {
    return m_strategy_gene->get_game_move(opponent);
}

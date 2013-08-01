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

using namespace pridil;


/*
 *  DNA class constructor
 *
 *  m_strategy_gene is a pointer, and the associated genes are created
 *  with the new operator, because we need polymorphism via a base
 *  class.
 *
 *  The other genes are created with pointers as each gene contains
 *  a reference to a Brain, which contains a DNA member, which contains
 *  Gene members ... so we need to forward declare.
 */

DNA::DNA(const Brain& brain, const CreatureInit& c_init) :
         m_brain(brain),
         m_strategy_gene(0),
         m_death_gene(new DeathGene(m_brain, c_init)),
         m_repro_gene(new ReproGene(m_brain, c_init)) {
    switch ( c_init.strategy ) {
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
 *  DNA destructor, deletes genes
 */

DNA::~DNA() {
    delete m_strategy_gene;
    delete m_death_gene;
    delete m_repro_gene;
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
 *  Returns true if age exceeds life expectancy.
 */

bool DNA::is_dead(Day age) const {
    return m_death_gene->is_dead(age);
}

/*
 *  Returns a reproduced creature.
 */

Creature * DNA::reproduce(int& resources) const {
    return m_repro_gene->reproduce(resources);
}

/*
 *  Gets a game move against a particular opponent.
 *
 *  The DNA object consults its strategy gene to determine the move.
 */

GameMove DNA::get_game_move(const CreatureID opponent) const {
    return m_strategy_gene->get_game_move(opponent);
}

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
         m_strategy_gene(StrategyGeneFactory(brain, c_init)),
         m_death_gene(new DeathGene(m_brain, c_init)),
         m_repro_gene(new ReproGene(m_brain, c_init)) {}


/*
 *  DNA destructor
 */

DNA::~DNA() {} 


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

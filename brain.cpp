/*
 *  brain.cpp
 *  =========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of Brain class for Prisoners' Dilemma simulation.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <iostream>

#include "brain.h"
#include "dna.h"
#include "memory.h"
#include "game.h"


/*
 *  Constructor.
 *
 *  No initialization needed.
 */

Brain::Brain(Strategy strategy) : m_dna(strategy),
                                  m_memory() {}


/*
 *  Destructor.
 */

Brain::~Brain() {}


/*
 *  Stores a memory of a game with a particular creature.
 *
 *  Argument: reference to a GameInfo object containing details
 *  of the game played.
 */

void Brain::store_memory(const GameInfo& g_info) {
    m_memory.store_memory(g_info);
}


/*
 *  Outputs the entire contents of memory.
 */

void Brain::show_detailed_memories(std::ostream& out) const {
    m_memory.show_detailed_memories(out);
}


/*
 *  Returns the name of the playing strategy contained in DNA
 */

const std::string Brain::strategy() const {
    return m_dna.strategy();
}


/*
 *  Gets a game move against the specified creature.
 *
 *  The move chosen may or may not depend upon previous interactions
 *  with that creature, depending on the strategy stored in the
 *  creature's DNA.
 */

GameMove Brain::get_game_move(const CreatureID opponent) {
    GameInfoList& opponent_memory = m_memory.get_memories(opponent);
    return m_dna.get_game_move(opponent_memory);
}

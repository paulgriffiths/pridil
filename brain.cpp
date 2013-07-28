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
 *  Gets a game move against a particular opponent.
 *
 *  The DNA object consults its strategy gene to determine the move.
 *
 *  Arguments:
 *    opponent_memory -- a list of the results of previous games with
 *                       a particular opponent. The DNA may, or may not,
 *                       use these memories to decide on its move,
 *                       depending on its particular strategy.
 *
 *  Returns:
 *    A GameMove object representing the move played.
 */

GameMove Brain::get_game_move(GameInfoList& opponent_memory) {
    return m_dna.get_game_move(opponent_memory);
}


/*
 *  Returns the memories list for games against the specified
 *  creature.
 */

GameInfoList& Brain::get_memories(CreatureID opponent_id) {
    return m_memory.get_memories(opponent_id);
}

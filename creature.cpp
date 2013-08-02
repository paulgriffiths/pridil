/*
 *  creature.cpp
 *  ============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of Creature class for Prisoners' Dilemma simulation.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <ostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include "creature.h"

using namespace pridil;


int Creature::c_next_id = 0;        // Initialize static class variable


/*
 *  Constructor. Note increment of static ID for next creature.
 */

Creature::Creature(const CreatureInit& c_init)
      : m_id(c_next_id++), m_brain(c_init), m_age(0),
        m_resources(c_init.starting_resources) {}


/*
 *  Destructor.
 */

Creature::~Creature() {
}


/*
 *  Returns a string describing the game-playing strategy
 *  in the creature's DNA.
 */

const std::string Creature::strategy() const {
    return m_brain.strategy();
}


/*
 *  Returns the creature's current id.
 */

int Creature::id() const {
    return m_id;
}


/*
 *  Returns the creature's current age.
 */

int Creature::age() const {
    return m_age;
}


/*
 *  Returns the amount of resources the creature currently has.
 */

int Creature::resources() const {
    return m_resources;
}


/*
 *  Returns the strategy enumeration
 */

Strategy Creature::strategy_value() const {
    return m_brain.strategy_value();
}


/*
 *  Returns true if the creature is dead, false otherwise.
 */

bool Creature::is_dead() const {
    return ((m_brain.is_dead(m_age) || m_resources <= 0) ? true : false);
}


/*
 *  Gets a game move against the specified creature.
 *
 *  The move chosen may or may not depend upon previous interactions
 *  with that creature, depending on the strategy stored in the
 *  creature's DNA.
 */

GameMove Creature::get_game_move(const CreatureID opponent) const {
    return m_brain.get_game_move(opponent);
}


/*
 *  Stores the detailed results of a game in memory.
 */

void Creature::give_game_result(const GameInfo& g_info) {
    m_resources += g_info.result;
    m_brain.store_memory(g_info);
}


/*
 *  Outputs the creature's detailed memories.
 */

void Creature::detailed_memories(std::ostream& out) const {
    m_brain.show_detailed_memories(out);
}


/*
 *  Member function ages the creature by one day.
 */

void Creature::age_day() {
    ++m_age;
}


/*
 *  Member function reproduces, if desired.
 *
 *  Returns:
 *    A pointer to the newly created creature, if successful, or to
 *    0 (NULL) if reproduction did not take place.
 */

Creature * Creature::reproduce() {
    return m_brain.reproduce(m_resources);
}

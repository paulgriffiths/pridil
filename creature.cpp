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

#include "creature.h"
#include "dna.h"

int Creature::c_next_id = 0;        // Initialize static class variable


/*
 *  Constructor.
 */

Creature::Creature(const CreatureInit& c_init)
      : m_id(0), m_age(0), m_life_expectancy(c_init.life_expectancy),
        m_life_expectancy_range(c_init.life_expectancy_range),
        m_resources(c_init.starting_resources),
        m_dna(c_init.strategy), m_memory() {
    m_id = c_next_id++;
}


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
    return m_dna.strategy();
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
 *  Gets a game move against the specified creature.
 *
 *  The move chosen may or may not depend upon previous interactions
 *  with that creature, depending on the strategy stored in the
 *  creature's DNA.
 */

GameMove Creature::get_game_move(const CreatureID opponent) {
    GameInfoList& opponent_memory = m_memory.get_memories(opponent);
    return m_dna.get_game_move(opponent_memory);
}


/*
 *  Stores the detailed results of a game in memory.
 */

void Creature::give_game_result(const GameInfo& g_info) {
    m_resources += g_info.result;
    m_memory.store_memory(g_info);
}


/*
 *  Outputs the creature's detailed memories.
 */

void Creature::detailed_memories(std::ostream& out) const {
    m_memory.show_detailed_memories(out);
}


/*
 *  Member function ages the creature by one day.
 */

void Creature::age_day() {
    m_age++;
}

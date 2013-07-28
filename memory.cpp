/*
 *  memory.h
 *  ========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of Memory class for Prisoners' Dilemma simulation.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <iostream>

#include "memory.h"
#include "game.h"


/*
 *  Constructor.
 *
 *  No initialization needed, except to set up empty memories map.
 */

Memory::Memory() : m_memories() {}


/*
 *  Destructor. Delete all the memories.
 */

Memory::~Memory() {

    //  Iterate through keys of each creature encountered...

    GameInfoMap::iterator i;
    for ( i = m_memories.begin(); i != m_memories.end(); ++i ) {

        // ...for each key get the associated memories list...

        GameInfoList& mem_list = i->second;

        // ...and then delete all the memories in that list.

        GameInfoList::iterator j;
        for ( j = mem_list.begin(); j != mem_list.end(); ++j ) {
            delete *j;
        }
    }
}


/*
 *  Stores a memory of a game with a particular creature.
 *
 *  Argument: reference to a GameInfo object containing details
 *  of the game played.
 */

void Memory::store_memory(const GameInfo& g_info) {

    //  Get a reference to the memories list for the creature
    //  played. Note that if the creature has not been played before,
    //  using the [] operator automatically creates an empty list.

    GameInfoList& mem_list = m_memories[g_info.id];


    //  Create a new GameInfo object, populate it using
    //  the supplied argument, and store it in the memories list.

    GameInfo * p_ginfo = new GameInfo(g_info);
    mem_list.push_back(p_ginfo);
}


/*
 *  Outputs the entire contents of memory.
 */

void Memory::show_detailed_memories(std::ostream& out) const {
    GameInfoMap::const_iterator i;

    for ( i = m_memories.begin(); i != m_memories.end(); ++i ) {
        const GameInfoList& mem_list = i->second;

        GameInfoList::const_iterator j;
        for ( j = mem_list.begin(); j != mem_list.end(); ++j ) {
            GameInfo * ginfo = *j;

            out << "C" << ginfo->id
                << ", R" << ginfo->result << ". "
                << game_move_name(ginfo->own_move)
                << " <--> "
                << game_move_name(ginfo->opponent_move)
                << std::endl;
        }
    }
}


/*
 *  Returns the memories list for games against the specified
 *  creature.
 */

GameInfoList& Memory::get_memories(CreatureID opponent_id) {
    return m_memories[opponent_id];
}


/*
 *  Returns true if there are memories of previous interactions with
 *  the specified creature, false if not.
 */

bool Memory::recognize(const CreatureID opponent) const {
    if ( m_memories.find(opponent) == m_memories.end() ) {
        return false;
    }
    else {
        return true;
    }
}

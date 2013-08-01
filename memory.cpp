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
#include "brain_complex.h"
#include "game.h"

using namespace pridil;


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

    for ( GameInfoMap::iterator itr = m_memories.begin();
          itr != m_memories.end(); ++itr ) {

        // ...for each key get the associated memories list...

        GameInfoList& memories_list = itr->second;

        // ...and then delete all the memories in that list.

        for ( GameInfoList::iterator gl_itr = memories_list.begin();
              gl_itr != memories_list.end(); ++gl_itr ) {
            delete *gl_itr;
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
    GameInfoList& mem_list = m_memories[g_info.id];
    mem_list.push_back(new GameInfo(g_info));
}


/*
 *  Outputs the entire contents of memory.
 */

void Memory::show_detailed_memories(std::ostream& out) const {
    for ( GameInfoMap::const_iterator map_itr = m_memories.begin();
          map_itr != m_memories.end(); ++map_itr ) {
        const GameInfoList& mem_list = map_itr->second;

        for ( GameInfoList::const_iterator mem_itr = mem_list.begin();
              mem_itr != mem_list.end(); ++mem_itr ) {
            GameInfo* ginfo = *mem_itr;

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
 *  Returns true if there are memories of previous interactions with
 *  the specified creature, false if not.
 */

bool Memory::recognize(const CreatureID opponent) const {
    bool recognized_opponent;
    GameInfoMap::const_iterator itr = m_memories.find(opponent);
    if ( itr == m_memories.end() ) {
        recognized_opponent = false;
    } else {
        recognized_opponent = true;
    }
    return recognized_opponent;
}


/*
 *  Returns the number of memories of the specified creature.
 */

unsigned int Memory::num_memories(const CreatureID opponent) const {
    GameInfoMap::const_iterator map_itr = m_memories.find(opponent);
    if ( map_itr == m_memories.end() ) {
        return 0;
    }
    const GameInfoList& opponent_memories = (*map_itr).second;
    return opponent_memories.size();
}


/*
 *  Remembers the specified opponent's last move.
 *  
 *  Arguments:
 *    opponent -- ID of opponent
 *    past -- number of memories to look back, default is 1, the most
 *            recent memory.
 */

GameMove Memory::remember_move(const CreatureID opponent,
                               const unsigned int past) const {
    
    //  Throw exception if there are fewer memories of this
    //  opponent than the one requested.

    if ( num_memories(opponent) < past ) {
        throw InvalidOpponentMemory();
    }

    //  Get an iterator to the end of the memories of this opponent

    GameInfoMap::const_iterator map_itr = m_memories.find(opponent);
    const GameInfoList& memories = (*map_itr).second;
    GameInfoList::const_iterator mem_itr = memories.end();

    //  ...back up the iterator to the desired memory

    unsigned int n = past;
    while ( n-- > 0 ) {
        --mem_itr;
    }

    //  ...and return the opponent's move contained in that memory.

    const GameInfo* gInfo = *mem_itr;
    return simplify_game_move(gInfo->opponent_move);
}

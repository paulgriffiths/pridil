/*
 *  memory.h
 *  ========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to Memory class for Prisoners' Dilemma simulation.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_MEMORY_H
#define PG_PRIDIL_MEMORY_H

#include <ostream>

#include "pridil_types.h"
#include "game.h"


class Memory {
    public:
        Memory();
        ~Memory();

        void store_memory(const GameInfo& g_info);
        GameInfoList& get_memories(CreatureID opponent_id);

        void show_detailed_memories(std::ostream& out) const;

    private:
        GameInfoMap m_memories;
};

#endif      // PG_PRIDIL_MEMORY_H

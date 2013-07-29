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


class Memory {
    public:
        Memory();
        ~Memory();

        //  Member functions for accessing memories

        bool recognize(const CreatureID opponent) const;
        GameMove remember_move(const CreatureID opponent,
                               const unsigned int past = 1) const;
        unsigned int num_memories(const CreatureID opponent) const;
        void show_detailed_memories(std::ostream& out) const;

        //  Member function for storing memories

        void store_memory(const GameInfo& g_info);

    private:
        GameInfoMap m_memories;
};

#endif      // PG_PRIDIL_MEMORY_H

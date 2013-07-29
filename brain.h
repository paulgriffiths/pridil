/*
 *  brain.h
 *  =======
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to Brain class for Prisoners' Dilemma simulation.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_BRAIN_H
#define PG_PRIDIL_BRAIN_H

#include <ostream>

#include "pridil_types.h"
#include "dna.h"
#include "memory.h"


class Brain {
    public:

        //  Constructor and destructor

        explicit Brain(const Strategy strategy);
        ~Brain();

        //  Member functions for accessing memories

        bool recognize(const CreatureID opponent) const;
        unsigned int num_memories(const CreatureID opponent) const;
        GameMove remember_move(const CreatureID opponent,
                               const unsigned int past = 1) const;
        void show_detailed_memories(std::ostream& out) const;

        //  Member function for storing memories

        void store_memory(const GameInfo& g_info);

        //  Member functions for accessing DNA

        const std::string strategy() const;
        Strategy strategy_value() const;
        GameMove get_game_move(const CreatureID opponent) const;

    private:
        DNA m_dna;
        Memory m_memory;
};

#endif      // PG_PRIDIL_BRAIN_H

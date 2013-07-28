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
#include "game.h"


class Brain {
    public:
        Brain(Strategy strategy);
        ~Brain();

        void show_detailed_memories(std::ostream& out) const;
        const std::string strategy() const;

        void store_memory(const GameInfo& g_info);
        GameMove get_game_move(const CreatureID opponent);
        bool recognize(const CreatureID opponent) const;

    private:
        DNA m_dna;
        Memory m_memory;
};

#endif      // PG_PRIDIL_BRAIN_H

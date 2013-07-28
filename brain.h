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
#include "memory.h"
#include "dna.h"
#include "game.h"


class Brain {
    public:
        Brain(Strategy strategy);
        ~Brain();

        void show_detailed_memories(std::ostream& out) const;
        const std::string strategy() const;

        void store_memory(const GameInfo& g_info);
        GameInfoList& get_memories(CreatureID opponent_id);
        GameMove get_game_move(GameInfoList& opponent_memory);

    private:
        DNA m_dna;
        Memory m_memory;
};

#endif      // PG_PRIDIL_BRAIN_H

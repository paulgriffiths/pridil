/*
 *  brain_complex.h
 *  ===============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to Brain complex. Attention to forward declarations is
 *  necessary since the Brain class has a DNA member variable, and DNA
 *  class contains a reference to its parent Brain. DNA class also has
 *  a StrategyGene member variable, which also receives that same
 *  reference to a Brain object. 
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_BRAIN_COMPLEX_H
#define PG_PRIDIL_BRAIN_COMPLEX_H

#include <ostream>
#include "pridil_common.h"


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


/*  Forward declarations for DNA class  */

class StrategyGene;
class Brain;


/*  DNA class  */

class DNA {
    public:

        //  Constructor and destructor

        explicit DNA(const Brain& brain, const Strategy strategy);
        ~DNA();

        //  Getter methods

        const std::string strategy() const;
        Strategy strategy_value() const;

        //  Genetic action methods

        GameMove get_game_move(const CreatureID opponent) const;


    private:
        const Brain& m_brain;
        StrategyGene * m_strategy_gene;

        DNA(const DNA&);                // Prevent copying
        DNA& operator=(const DNA&);     // Prevent assignment

};


/*  Brain class  */

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

#endif      // PG_PRIDIL_BRAIN_COMPLEX_H

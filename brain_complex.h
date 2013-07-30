/*
 *  brain_complex.h
 *  ===============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to Brain complex.
 *
 *  The "brain complex" consists of:
 *   - DNA, which controls certain actions, and to which certain
 *     decisions are referred;
 *   - Memory, which stores memories of previous experiences, which
 *     may influence actions and decisions; and
 *   - Brain, which owns and acts as the interface between DNA and Memory
 *     (DNA may consult Memory when making certain decisions), and which
 *     acts as an interface between the Creature owning the Brain, and its
 *     DNA and Memory. A liberty has been taken with the name, since DNA
 *     does not belong to the brain in real organisms.
 *
 *  Attention to forward declarations is necessary since the Brain class
 *  has a DNA member variable, and DNA class contains a reference to its
 *  parent Brain. DNA class also has a StrategyGene member variable, which
 *  also receives that same reference to a Brain object. Defining the
 *  Brain, DNA and Memory classes within this single header file ensures
 *  the references are appropriately handled.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_BRAIN_COMPLEX_H
#define PG_PRIDIL_BRAIN_COMPLEX_H

#include <ostream>
#include "pridil_common.h"

namespace pridil {

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

class Creature;
class DeathGene;
class ReproGene;
class StrategyGene;
class Brain;


/*  DNA class  */

class DNA {
    public:

        //  Constructor and destructor

        explicit DNA(const Brain& brain, const CreatureInit& c_init);
        ~DNA();

        //  Getter methods

        const std::string strategy() const;
        Strategy strategy_value() const;
        bool is_dead(Day age) const;
        Creature * reproduce(int& resources) const;

        //  Genetic action methods

        GameMove get_game_move(const CreatureID opponent) const;


    private:
        const Brain& m_brain;
        StrategyGene * m_strategy_gene;
        DeathGene * m_death_gene;
        ReproGene * m_repro_gene;

        DNA(const DNA&);                // Prevent copying
        DNA& operator=(const DNA&);     // Prevent assignment
};


/*  Brain class  */

class Brain {
    public:

        //  Constructor and destructor

        explicit Brain(const CreatureInit& c_init);
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
        bool is_dead(Day age) const;
        Creature * reproduce(int& resources) const;
        GameMove get_game_move(const CreatureID opponent) const;

    private:
        DNA m_dna;
        Memory m_memory;
};

}       //  namespace pridil

#endif      // PG_PRIDIL_BRAIN_COMPLEX_H

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
 *     does not belong to the brain in real organisms. A primary motivation
 *     of providing the Brain class is to avoid exposing the Memory interface
 *     (which the DNA sometimes needs to access) in the main Creature
 *     interface.
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
#include <memory>
#include "pridil_common.h"

namespace pridil {

/*
 *  Memory class.
 *
 *  Stores and recalls memories of games with individual opponents.
 *
 *  Public member functions:
 *    recognize() - returns true if the specified oppoent has been
 *                  encountered before.
 *
 *    remember_move() - recalls a recent memory of the specified opponent.
 *
 *    num_memories() - returns how many times the specified opponent has
 *                     been encountered before.
 *
 *    show_detailed_memories() - outputs details of all stored memories.
 *
 *    store_memory() - stores a memory of the specified game.
 */

class Memory {
    public:
        Memory();
        ~Memory();

        //  Member functions for accessing memories

        bool recognize(const CreatureID opponent) const;
        unsigned int num_memories(const CreatureID opponent) const;
        GameMove remember_move(const CreatureID opponent,
                               const unsigned int past = 1) const;
        void show_detailed_memories(std::ostream& out) const;

        //  Member function for storing memories

        void store_memory(const GameInfo& g_info);

    private:
        GameInfoMap m_memories;

        Memory(const Memory&);                  // Prevent copying
        Memory& operator=(const Memory&);       // Prevent assignment
};


/*  Forward declarations necessary for for DNA class  */

class Creature;
class DeathGene;
class ReproGene;
class StrategyGene;
class Brain;


/*
 *  DNA class.
 *
 *  Stores the creatures 'genetic' characteristics, and make decisions
 *  or performs actions based on them.
 *
 *  Public member functions:
 *    strategy() - returns a std::string representation of the DNA's
 *                 game-playing strategy.
 *
 *    strategy_value() - returns a Strategy enumeration representation of
 *                       the DNA's game-playing strategy.
 *
 *    is_dead() - returns true if the specified age exceeds the life
 *                expectancy contained within the DNA.
 *
 *    reproduce() - returns a pointer to a newly created offspring if
 *                  the specified amount of resources exceeds the
 *                  cost of reproduction contained within the DNA. The
 *                  function modifies and deducts the cost of reproduction
 *                  from the resources provided.
 *
 *    get_game_move() - returns a game move against the specified opponent.
 *                      Depending on the strategy contained within the DNA,
 *                      this move may or may not be influenced by memories
 *                      of previous interactions with that opponent.
 */

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
        std::auto_ptr<StrategyGene> m_strategy_gene;
        std::auto_ptr<DeathGene> m_death_gene;
        std::auto_ptr<ReproGene> m_repro_gene;

        DNA(const DNA&);                // Prevent copying
        DNA& operator=(const DNA&);     // Prevent assignment
};


/*
 *  Brain class.
 *
 *  Contains, and acts as an interface with and between, the Memory
 *  and the DNA.
 *
 *  The public member functions merely call the Memory and DNA member
 *  functions of the same name.
 */

class Brain {
    public:

        //  Constructor and destructor

        explicit Brain(const CreatureInit& c_init);
        ~Brain();

        //  Memory interface member functions

        bool recognize(const CreatureID opponent) const;
        unsigned int num_memories(const CreatureID opponent) const;
        GameMove remember_move(const CreatureID opponent,
                               const unsigned int past = 1) const;
        void show_detailed_memories(std::ostream& out) const;
        void store_memory(const GameInfo& g_info);

        //  DNA interface member functions

        const std::string strategy() const;
        Strategy strategy_value() const;
        bool is_dead(Day age) const;
        Creature * reproduce(int& resources) const;
        GameMove get_game_move(const CreatureID opponent) const;

    private:
        DNA m_dna;
        Memory m_memory;

        Brain(const Brain&);                // Prevent copying
        Brain& operator=(const Brain&);     // Prevent assignment
};

}       //  namespace pridil

#endif      // PG_PRIDIL_BRAIN_COMPLEX_H

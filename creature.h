/*
 *  creature.h
 *  ==========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to Creature class for Prisoner's Dilemma simulation.
 *
 *  A Creature is the basic actor in the Pridil world. It can:
 *   - play iterations of the prisoner's dilemma game with other Creatures;
 *   - remember those interactions;
 *   - acquire or lose resources as a result of those interactions;
 *   - age;
 *   - die when it runs out of resources or reaches its life expectancy;
 *   - reproduce when it has sufficient resources;
 *
 *  The way in which a Creature plays iterations of the prisoner's
 *  dilemma game with other creatures is determined by the strategy
 *  contained within a specific gene in its DNA, which is turn may
 *  consult the Creature's Memory in coming to its decision. A
 *  Creature's DNA and Memory are contained within its Brain.
 *
 *  Public member functions:
 *    id() - returns the creature's numeric identifier.
 *
 *    age() - returns the creature's current age.
 *
 *    resources() - returns the quantity of resources the creature
 *                  currently has.
 *
 *    is_dead() - returns true if the creatre is dead due to age, or
 *                due to exhausted resources.
 *
 *    strategy() - returns a std::string representation of the creature's
 *                 game-playing strategy.
 *
 *    strategy_value() - returns a Strategy enumeration representation of
 *                       the creature's game-playing strategy.
 *
 *    detailed_memories() - outputs all of the creature's memories.
 *
 *    get_game_move() - returns a game move against a specified opponent.
 *                      The move will be calculated based on the creature's
 *                      game-playing strategy which, depending on the
 *                      individual strategy, may or may not consult memories
 *                      of previous interactions with the specified opponent.
 *
 *    give_game_result() - stores the provided game result in memory.
 *
 *    age_day() - ages the creature by one day.
 *
 *    reproduce() - returns a pointer to a newly created creature if the
 *                  creature's resources are sufficient to reproduce.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_CREATURE_H
#define PG_PRIDIL_CREATURE_H

#include <ostream>
#include <string>
#include "pridil_common.h"
#include "brain_complex.h"


namespace pridil {

/*
 *  Creature class.
 */

class Creature {
    public:

        //  Constructor and destructor

        explicit Creature(const CreatureInit& cInit);
        ~Creature();

        //  Getter methods

        int id() const;
        int age() const;
        int resources() const;
        bool is_dead() const;
        const std::string strategy() const;
        Strategy strategy_value() const;
        void detailed_memories(std::ostream& out) const;

        //  Gaming and aging methods

        GameMove get_game_move(const CreatureID opponent) const;
        void give_game_result(const GameInfo& g_info);
        void age_day();

        //  Reproduction member function

        Creature * reproduce();

    private:
        static int c_next_id;

        CreatureID m_id;
        Brain m_brain;
        Day m_age;
        int m_resources;


    //  Make comparison function objects friends to access data

    friend class CompareCreatureByID;
};


/*
 *  Typedef for CreatureList
 */

typedef std::vector<Creature *> CreatureList;


/*
 *  Function object used for sorting CreatureLists
 */

class CompareCreatureByID {
    public:
        bool operator()(const Creature * c1, const Creature * c2) const {
            return c1->m_id < c2->m_id;
        }
};

}       //  namespace pridil

#endif      // PG_PRIDIL_CREATURE_H

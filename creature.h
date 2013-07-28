/*
 *  creature.h
 *  ==========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to Creature class for Prisoners' Dilemma simulation.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_CREATURE_H
#define PG_PRIDIL_CREATURE_H

#include <ostream>
#include <string>

#include "dna.h"
#include "memory.h"
#include "pridil_types.h"


/*
 *  Structure used to initialize a Creature instance
 */

struct CreatureInit {
    Day life_expectancy;
    Day life_expectancy_range;
    Strategy strategy;
    int starting_resources;

    CreatureInit() :
        life_expectancy(0), life_expectancy_range(0),
        strategy(random_strategy), starting_resources(0) {}

    CreatureInit(const Day& le, const Day& ler,
                 const Strategy& stgy, const int res) :
        life_expectancy(le), life_expectancy_range(ler),
        strategy(stgy), starting_resources(res) {}
};


/*
 *  Creature class
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
        void detailed_memories(std::ostream& out) const;


        //  Gaming and aging methods

        GameMove get_game_move(const CreatureID opponent);
        void give_game_result(const GameInfo& g_info);
        void age_day();


    private:
        static int c_next_id;

        CreatureID m_id;
        Day m_age;
        Day m_life_expectancy;
        Day m_life_expectancy_range;
        int m_resources;
        DNA m_dna;
        Memory m_memory;


    //  Make comparison function objects friends to access data

    friend class CompareCreatureByID;

};


/*
 *  Function object used for sorting CreatureLists
 */

class CompareCreatureByID {
    public:
        bool operator()(const Creature * c1, const Creature * c2) const {
            return c1->m_id < c2->m_id;
        }
};

#endif      // PG_PRIDIL_CREATURE_H

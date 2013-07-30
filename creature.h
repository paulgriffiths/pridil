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

#include "pridil_common.h"
#include "brain_complex.h"


namespace pridil {


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

        GameMove get_game_move(const CreatureID opponent) const;
        void give_game_result(const GameInfo& g_info);
        void age_day();

        //  Reproduction member function

        Creature * reproduce();

    private:
        static int c_next_id;

        CreatureID m_id;
        Day m_age;
        Day m_life_expectancy;
        Day m_life_expectancy_range;
        int m_resources;
        int m_repro_cost;
        int m_repro_min_resources;
        Brain m_brain;


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

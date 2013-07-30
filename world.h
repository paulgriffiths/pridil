/*
 *  world.h
 *  =======
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to World class for Prisoners' Dilemma simulation.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_WORLD_H
#define PG_PRIDIL_WORLD_H

#include <ostream>
#include <vector>

#include "pridil_common.h"
#include "creature.h"


//  World class

class World {
    public:

        //  Constructor and destructor

        explicit World(const WorldInfo& wInfo);
        ~World();


        //  Methods to advance and show the current world day

        Day day() const;
        void advance_day();


        //  Methods to output simulation results statistics

        void output_world_stats(std::ostream& out) const;
        void output_summary_creature_stats(std::ostream& out) const;
        void output_full_creature_stats(std::ostream& out) const;
        void output_summary_resources_by_strategy(std::ostream& out) const;
        void output_summary_dead_by_strategy(std::ostream& out) const;

    private:

        //  Regular member variables

        WorldInfo m_wInfo;
        Day m_day;
        unsigned long m_games_played;
        CreatureList m_creatures;
        CreatureList m_dead_creatures;


        //  Method to play a game between two creatures

        void play_game(Creature * player1, Creature * player2);
};

#endif      // PG_PRIDIL_WORLD_H

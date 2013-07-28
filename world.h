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

#include "creature.h"
#include "pridil_types.h"


//  WorldInfo structure for holding attributes about the
//  simulated world, including number of different types
//  of creature, starting resources, and so on.

struct WorldInfo {
    int m_random_strategy;
    int m_tit_for_tat;
    int m_tit_for_two_tats;
    int m_susp_tit_for_tat;
    int m_naive_prober;
    int m_always_cooperate;
    int m_always_defect;
    Day m_default_life_expectancy;
    Day m_default_life_expectancy_range;
    Day m_days_to_run;
    int m_default_starting_resources;
    bool m_disable_deaths;

    WorldInfo() :
        m_random_strategy(1), m_tit_for_tat(1),
        m_tit_for_two_tats(1), m_susp_tit_for_tat(1),
        m_naive_prober(1),
        m_always_cooperate(1), m_always_defect(1),
        m_default_life_expectancy(100), m_default_life_expectancy_range(0),
        m_days_to_run(10), m_default_starting_resources(100),
        m_disable_deaths(false) {}
};


//  Word class

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

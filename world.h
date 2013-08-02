/*
 *  world.h
 *  =======
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to World class for Prisoner's Dilemma simulation.
 *
 *  The World class is the controlling class in the simulation, and the
 *  only class available to the user. Its functions are to:
 *
 *   - create a population of creatures with the specified
 *     characteristics;
 *   - cause those creatures to play iterations of the prisoner's
 *     dilemma with each other; and to
 *   - provide statistics about the population and the iterations played.
 *
 *  Public member functions:
 *    day() - returns the current world day.
 *
 *    advance_day() - advances the world by one day, including playing all
 *                    that day's games, ageing each creature by one day,
 *                    and processing any creatures which died or were born
 *                    on that day.
 *
 *    output_world_stats() - outputs summary statistics of the world,
 *                           including number of days passed, number of
 *                           games played, number of creatures that died
 *                           or were born, etc.
 *
 *    output_summary_creature_stats() - outputs summary statistics about
 *                           each individual creature, including its
 *                           game-playing strategy and the quantity of
 *                           resources it ended with.
 *
 *    output_full_creature_stats() - outputs full statistics about each
 *                           individual creature, including a full list of
 *                           the details of the games it played.
 *
 *    output_summary_resources_by_strategy() - outputs summary statistics
 *                           for all creatures of each game-playing
 *                           strategy, including the minimum, maximum, and
 *                           average resources held by creatures having
 *                           that strategy.
 *    
 *    output_summary_dead_by_strategy() - outputs summary statistics showing
 *                           the number of creatures of each game-playing
 *                           strategy that died during the world time.
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

namespace pridil {

class World {
    public:

        //  Constructor and destructor

        explicit World(const WorldInfo& wInfo);
        ~World();

        //  Methods to show and advance the current world day

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

}       //  namespace pridil

#endif      // PG_PRIDIL_WORLD_H

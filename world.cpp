/*
 *  world.cpp
 *  =========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of World class for Prisoners' Dilemma simulation.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <iostream>
#include <ostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <utility>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "pridil_common.h"
#include "world.h"
#include "creature.h"
#include "game.h"


using std::endl;
using std::ostream;
using std::sort;
using std::random_shuffle;
using std::vector;
using std::map;
using std::string;
using std::max;
using std::min;
using std::pair;

using namespace pridil;


/*
 *  Constructor.
 */

World::World(const WorldInfo& wInfo) : m_wInfo(wInfo),
                        m_day(1),
                        m_games_played(0),
                        m_creatures(),
                        m_dead_creatures() {

    //  Seed the pseudo-random number generator

    std::srand((unsigned) std::time(0));

    //  Populate vector with correct numbers of creatures

    CreatureInit c_init;
    c_init.life_expectancy = wInfo.m_default_life_expectancy;
    c_init.life_expectancy_range = wInfo.m_default_life_expectancy_range;
    c_init.starting_resources = wInfo.m_default_starting_resources;
    c_init.repro_cost = wInfo.m_repro_cost;
    c_init.repro_min_resources = wInfo.m_repro_min_resources;

    try {
        for ( int i = 0; i < wInfo.m_random_strategy; ++i ) {
            c_init.strategy = random_strategy;
            m_creatures.push_back(new Creature(c_init));
            m_wInfo.m_starting_creatures++;
        }
        for ( int i = 0; i < wInfo.m_tit_for_tat; ++i ) {
            c_init.strategy = tit_for_tat;
            m_creatures.push_back(new Creature(c_init));
            m_wInfo.m_starting_creatures++;
        }
        for ( int i = 0; i < wInfo.m_tit_for_two_tats; ++i ) {
            c_init.strategy = tit_for_two_tats;
            m_creatures.push_back(new Creature(c_init));
            m_wInfo.m_starting_creatures++;
        }
        for ( int i = 0; i < wInfo.m_susp_tit_for_tat; ++i ) {
            c_init.strategy = susp_tit_for_tat;
            m_creatures.push_back(new Creature(c_init));
            m_wInfo.m_starting_creatures++;
        }
        for ( int i = 0; i < wInfo.m_naive_prober; ++i ) {
            c_init.strategy = naive_prober;
            m_creatures.push_back(new Creature(c_init));
            m_wInfo.m_starting_creatures++;
        }
        for ( int i = 0; i < wInfo.m_always_cooperate; ++i ) {
            c_init.strategy = always_cooperate;
            m_creatures.push_back(new Creature(c_init));
            m_wInfo.m_starting_creatures++;
        }
        for ( int i = 0; i < wInfo.m_always_defect; ++i ) {
            c_init.strategy = always_defect;
            m_creatures.push_back(new Creature(c_init));
            m_wInfo.m_starting_creatures++;
        }
    } catch(...) {

        //  Free allocated creatures if there was any problem
        //  with construction

        CreatureList::iterator itr_live_creature;
        for ( itr_live_creature = m_creatures.begin();
              itr_live_creature != m_creatures.end();
              ++itr_live_creature ) {
            delete *itr_live_creature;
        }

        throw;                      // Re-throw exception to caller
    }
}


/*
 *  Destructor. Deletes all allocated creatures.
 */

World::~World() {

    //  Assert that creature counts are consistent

    assert((m_creatures.size() + m_dead_creatures.size()) == 
           (m_wInfo.m_starting_creatures + m_wInfo.m_born_creatures));
    assert(m_dead_creatures.size() == m_wInfo.m_dead_creatures);
    assert(m_creatures.size() == (m_wInfo.m_starting_creatures +
           m_wInfo.m_born_creatures - m_wInfo.m_dead_creatures));


    //  Delete dynamically allocated creatures.

    CreatureList::iterator itr_live_creature;
    for ( itr_live_creature = m_creatures.begin();
          itr_live_creature != m_creatures.end();
          ++itr_live_creature ) {
        delete *itr_live_creature;
    }

    CreatureList::iterator itr_dead_creature;
    for ( itr_dead_creature = m_dead_creatures.begin();
          itr_dead_creature != m_dead_creatures.end();
          ++itr_dead_creature ) {
        delete *itr_dead_creature;
    }
}


/*
 *  Returns the current world day.
 */

Day World::day() const {
    return m_day;
}


/*
 *  Completes a world day.
 *
 *  Each creature (unless there is an odd number of creatures, in which case
 *  one of them sits out) is paired with a random other creature and a
 *  game is played between them. Each creature plays one game per day.
 *
 *  The randomizing is accomplished by random_shuffle()ing the list
 *  of creatures, and pairing up 0 with 1, 2 with 3, and so on.
 */

void World::advance_day() {
    random_shuffle(m_creatures.begin(), m_creatures.end());

    //  Play paired games

    CreatureList::iterator itr_c1;
    CreatureList::iterator itr_c2;
    for ( itr_c1 = m_creatures.begin(), itr_c2 = itr_c1 + 1;
          itr_c1 != m_creatures.end() && itr_c1 != (m_creatures.end() - 1);
          itr_c1 += 2, itr_c2 += 2 ) {
        play_game(*itr_c1, *itr_c2);
        ++m_games_played;
    }

    //  Age each creature a day, checking for deaths and births
    //  Note that we can't increment itr_creature within the
    //  for loop, because we have to use std::vector.erase() to
    //  get the next position when we remove a dead creature from
    //  the list.

    CreatureList newborns;
    for ( CreatureList::iterator itr_creature = m_creatures.begin();
          itr_creature != m_creatures.end(); /* empty expression */ ) {

        Creature* creature = *itr_creature;
        creature->age_day();

        //  Check for deaths and reproductions

        if ( (m_wInfo.m_disable_deaths != true) && creature->is_dead() ) {
            m_dead_creatures.push_back(creature);
            itr_creature = m_creatures.erase(itr_creature);
            ++m_wInfo.m_dead_creatures;
        } else if ( (m_wInfo.m_disable_repro != true) &&
                    (m_day % m_wInfo.m_repro_cycle_days) == 0 ) {
            Creature* new_creature = creature->reproduce();
            if ( new_creature ) {
                newborns.push_back(new_creature);
                ++m_wInfo.m_born_creatures;
            }
            ++itr_creature;
        } else {
            ++itr_creature;
        }
    }

    //  Add any newborns to live creatures list

    if ( newborns.empty() != true ) {
        m_creatures.insert(m_creatures.end(), newborns.begin(), newborns.end());
    }

    //  Increment world days

    ++m_day;
}


/*
 *  Member function outputs summary statistics for the world.
 *
 *  Arguments: reference to a ostream object to which to output.
 */

void World::output_world_stats(ostream& out) const {
    out << "Summary world statistics:" << endl
        << "Days passed: " << m_day - 1 << endl
        << "Games played: " << m_games_played << endl
        << "Starting creatures: " << m_wInfo.m_starting_creatures << endl
        << "Living creatures: " << m_creatures.size() << endl
        << "Creatures born: " << m_wInfo.m_born_creatures << endl
        << "Creatures died: " << m_wInfo.m_dead_creatures << endl
        << endl;
}


/*
 *  Member function outputs summary statistics for all living creatures
 *  currently in the world.
 *
 *  Arguments: reference to a ostream object to which to output.
 */

void World::output_summary_creature_stats(ostream& out) const {
    CreatureList templist = m_creatures;
    sort(templist.begin(), templist.end(), CompareCreatureByID());

    out << "Summary creature statistics:" << endl;
    for ( CreatureList::const_iterator itr = templist.begin();
          itr != templist.end(); ++itr ) {
        const Creature* creature = *itr;

        out << "Creature " << creature->id()
            << ", strategy '" << creature->strategy()
            << "', resources " << creature->resources()
            << endl;
    }
    out << endl;
}


/*
 *  Member function outputs detailed statistics for all living creatures
 *  currently in the world.
 *
 *  Arguments: reference to a ostream object to which to output.
 */

void World::output_full_creature_stats(ostream& out) const {
    for ( CreatureList::const_iterator itr = m_creatures.begin();
          itr != m_creatures.end(); ++itr ) {

        const Creature* creature = *itr;

        out << "=============\nCreature " << creature->id()
            << "\n=============\n\n";

        out << "Strategy : " << creature->strategy() << "\n";
        out << "Age      : " << creature->age() << "\n";
        out << "Resources: " << creature->resources() << "\n";
        out << endl;

        creature->detailed_memories(out);
    }
}


/*
 *  Resources statistics structure used by following method.
 *
 *  Note, this cannot be defined locally prior to C++11 as it
 *  is used within a template.
 */

namespace {
    struct ResStat {
        int num_creatures;
        int max_res;
        int min_res;
        double avg_res;

        ResStat() : num_creatures(0),
                    max_res(std::numeric_limits<int>().min()),
                    min_res(std::numeric_limits<int>().max()),
                    avg_res(0) {}
    };
}


/*
 *  Member function outputs summary resources statistics for the
 *  strategies of all living currently in the world.
 *
 *  Arguments: reference to a ostream object to which to output.
 */

void World::output_summary_resources_by_strategy(ostream& out) const {

    typedef map<string, ResStat> MSR;
    typedef vector<pair<double, string> > VPDS;

    MSR resources_map;
    VPDS srtd_strgy;

    //  Summarize statistics by strategy into resources_map

    for ( CreatureList::const_iterator itr = m_creatures.begin();
          itr != m_creatures.end(); ++itr ) {
        const Creature* creature = *itr;
        ResStat& stats = resources_map[creature->strategy()];
        const int creat_res = creature->resources();

        stats.num_creatures += 1;
        stats.min_res = min(stats.min_res, creat_res);
        stats.max_res = max(stats.max_res, creat_res);
        stats.avg_res = (stats.avg_res * (stats.num_creatures - 1) +
                         creat_res) / stats.num_creatures;
    }

    //  Sort strategies by average resources, low to high

    for ( MSR::iterator itr = resources_map.begin();
          itr != resources_map.end(); ++itr ) {
        const string strategy = itr->first;
        const ResStat& stats = itr->second;
        srtd_strgy.push_back(make_pair(stats.avg_res, strategy));
    }
    sort(srtd_strgy.begin(), srtd_strgy.end());


    //  Output summary resource statistcs from high to low, using
    //  a reverse iterator

    int ranking = 1;
    out << "Summary resource statistics by strategy:" << endl;
    for ( VPDS::reverse_iterator itr = srtd_strgy.rbegin();
            itr != srtd_strgy.rend(); ++itr ) {
        const string strategy = itr->second;
        const ResStat& stats = resources_map[strategy];

        out << ranking++ << ", "
            << strategy << " (" << stats.num_creatures << "): "
            << "max " << stats.max_res
            << ", min " << stats.min_res
            << ", sprd " << stats.max_res - stats.min_res
            << ", avg " << stats.avg_res
            << endl;
    }
    out << endl;
}


/*
 *  Member function outputs summary statistics for the number of
 *  creatures by strategy that have died.
 *
 *  Arguments: reference to a ostream object to which to output.
 */

void World::output_summary_dead_by_strategy(ostream& out) const {
    if ( m_wInfo.m_disable_deaths ) {
        return;
    }

    typedef map<string, int> MSI;

    MSI strategy_map;

    //  Summarize number of deaths by strategy into strategy_map

    for ( CreatureList::const_iterator itr = m_dead_creatures.begin();
          itr != m_dead_creatures.end(); ++itr ) {
        const Creature* creature = *itr;
        strategy_map[creature->strategy()]++;
    }


    //  Output summary death statistics

    out << "Summary deaths by strategy:" << endl;
    for ( MSI::const_iterator itr = strategy_map.begin();
            itr != strategy_map.end(); ++itr ) {
        const string strategy = itr->first;
        const int number_dead = itr->second;
        out << number_dead << " "
            << strategy << " creature"
            << (number_dead > 1 ? "s" : "") << " died."
            << endl;
    }
    out << endl;
}


/*
 *  Member function plays a game between two creatures.
 *
 *  Each creature is asked for a move, and told the ID of their
 *  opponent so that they can remember previous games with that
 *  opponent. The result of the game is calculated, and each
 *  creature is informed of the result so that they can update
 *  their memories.
 *
 *  Arguments: a pointer to each of the two creatures playing.
 */

void World::play_game(Creature * creature1, Creature * creature2) {

    //  Get the move from each of the two creatures

    GameMove c1move = creature1->get_game_move(creature2->id());
    GameMove c2move = creature2->get_game_move(creature1->id());

    //  Populate GameInfo objects for each creature, and
    //  populate with the game result.

    GameInfo c1info(creature2->id(), c1move, c2move, 0);
    GameInfo c2info(creature1->id(), c2move, c1move, 0);
    game_result(c1info, c2info);

    //  Communicate results of the game to each creature

    creature1->give_game_result(c1info);
    creature2->give_game_result(c2info);
}

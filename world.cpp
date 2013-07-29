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

#include "world.h"
#include "creature.h"

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

    CreatureList::iterator i;
    for ( i = m_creatures.begin(); i != m_creatures.end(); ++i ) {
        if ( *i != 0 ) {
            delete *i;
        }
    }

    for ( i = m_dead_creatures.begin(); i != m_dead_creatures.end(); ++i ) {
        if ( *i != 0 ) {
            delete *i;
        }
    }
}


/*
 *  Member function returns the current world day.
 */

Day World::day() const {
    return m_day;
}


/*
 *  Member function completes a world day.
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

    CreatureList::iterator itm1;
    CreatureList::iterator itm2;
    for ( itm1 = m_creatures.begin(), itm2 = itm1 + 1;
          itm1 != m_creatures.end() && itm1 != (m_creatures.end() - 1);
          itm1 += 2, itm2 += 2 ) {
        play_game(*itm1, *itm2);
        m_games_played += 1;
    }

    //  Age each creature a day

    CreatureList::iterator i;
    for ( i = m_creatures.begin(); i != m_creatures.end(); ) {
        (*i)->age_day();

        //  Check for deaths

        if ( (m_wInfo.m_disable_deaths != true) && (*i)->is_dead() ) {
            m_dead_creatures.push_back(*i);
            CreatureList::iterator temp = m_creatures.erase(i);
            i = temp;
            ++m_wInfo.m_dead_creatures;
        } else {
            ++i;
        }
    }

    //  Increment world days

    ++m_day;
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


/*
 *  Member function outputs summary statistics for the world.
 *
 *  Arguments: reference to a ostream object to which to output.
 */

void World::output_world_stats(ostream& out) const {
    out << "Summary world statistics:" << endl
        << "Days passed: " << m_day - 1 << endl
        << "Games played: " << m_games_played << endl
        << endl;
}


/*
 *  Member function outputs detailed statistics for all living creatures
 *  currently in the world.
 *
 *  Arguments: reference to a ostream object to which to output.
 */

void World::output_full_creature_stats(ostream& out) const {
    CreatureList::const_iterator i;

    for ( i = m_creatures.begin(); i != m_creatures.end(); ++i ) {

        //  Output individual creature header

        out << "=============\nCreature " << (*i)->id()
            << "\n=============\n\n";


        //  Output strategy, age and resources

        out << "Strategy : " << (*i)->strategy() << "\n";
        out << "Age      : " << (*i)->age() << "\n";
        out << "Resources: " << (*i)->resources() << "\n";
        out << endl;


        //  Output detailed memories

        (*i)->detailed_memories(out);
    }
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

    CreatureList::iterator i;
    out << "Summary creature statistics:" << endl;
    for ( i = templist.begin(); i != templist.end(); ++i ) {
        out << "Creature " << (*i)->id()
            << ", strategy '" << (*i)->strategy()
            << "', resources " << (*i)->resources()
            << endl;
    }
    out << endl;
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

        ResStat() : num_creatures(0), max_res(std::numeric_limits<int>().min()),
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

    for ( CreatureList::const_iterator i = m_creatures.begin();
          i != m_creatures.end(); ++i ) {
        ResStat& tmp = resources_map[(*i)->strategy()];
        int creat_res = (*i)->resources();

        tmp.num_creatures += 1;
        tmp.min_res = min(tmp.min_res, creat_res);
        tmp.max_res = max(tmp.max_res, creat_res);
        tmp.avg_res = (tmp.avg_res * (tmp.num_creatures - 1) + creat_res) /
                       tmp.num_creatures;
    }


    //  Sort strategies by average resources, low to high

    for ( MSR::iterator im = resources_map.begin();
          im != resources_map.end(); ++im ) {
        srtd_strgy.push_back(make_pair(im->second.avg_res, im->first));
    }
    sort(srtd_strgy.begin(), srtd_strgy.end());


    //  Output summary resource statistcs from high to low, using
    //  a reverse iterator

    int n = 1;
    out << "Summary resource statistics by strategy:" << endl;
    for ( VPDS::reverse_iterator id = srtd_strgy.rbegin();
            id != srtd_strgy.rend(); ++id ) {
        ResStat& tmp = resources_map[id->second];

        out << n++ << ", "
            << id->second << " (" << tmp.num_creatures << "): "
            << "max " << tmp.max_res
            << ", min " << tmp.min_res
            << ", sprd " << tmp.max_res - tmp.min_res
            << ", avg " << tmp.avg_res
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

    for ( CreatureList::const_iterator i = m_dead_creatures.begin();
          i != m_dead_creatures.end(); ++i ) {
        strategy_map[(*i)->strategy()]++;
    }


    //  Output summary death statistics

    out << "Summary deaths by strategy:" << endl;
    for ( MSI::const_iterator id = strategy_map.begin();
            id != strategy_map.end(); ++id ) {
        out << id->second << " "
            << id->first << " creature"
            << (id->second > 1 ? "s" : "") << " died."
            << endl;
    }
    out << endl;
}

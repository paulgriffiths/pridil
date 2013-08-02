/*
 *  pridil_common_types.h
 *  =====================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Common types for iterated prisoner's dilemma simulation.
 *
 *  The classes, structs, enumerations, exceptions and typedefs
 *  defined herein are self-contained, and are widely used by a variety
 *  of the main classes within the simulation, and are defined in a
 *  single file for ease of access and to avoid the need for
 *  forward declarations.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_COMMON_TYPES_H
#define PG_PRIDIL_COMMON_TYPES_H

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <list>
#include "pridil_exceptions.h"

namespace pridil {

//  Simple typedefs

typedef int CreatureID;
typedef int Day;

//  Enumerations

enum GameMove { coop, defect, coop_recip, defect_retal,
                coop_random, defect_random };

enum Strategy { random_strategy, tit_for_tat, susp_tit_for_tat,
                tit_for_two_tats, grudger, naive_prober, remorseful_prober,
                always_cooperate, always_defect };


//  Structures and classes

/*
 *  Structure used to initialize a Creature instance
 */

struct CreatureInit {
    Day life_expectancy;
    Day life_expectancy_range;
    Strategy strategy;
    int starting_resources;
    int repro_cost;
    int repro_min_resources;

    CreatureInit() :
        life_expectancy(0), life_expectancy_range(0),
        strategy(random_strategy), starting_resources(0),
        repro_cost(0), repro_min_resources(0) {}

    CreatureInit(const Day& le, const Day& ler,
                 const Strategy& stgy, const int res,
                 const int rc, const int rmr) :
        life_expectancy(le), life_expectancy_range(ler),
        strategy(stgy), starting_resources(res),
        repro_cost(rc), repro_min_resources(rmr) {}
};


/*
 *  Structure to record the result of a game, used as the basis of
 *  Creature memories of previous interactions with a given
 *  opponent.
 */

struct GameInfo {
    CreatureID id;
    GameMove own_move;
    GameMove opponent_move;
    int result;

    GameInfo(const GameInfo& gInfo) :
        id(gInfo.id), own_move(gInfo.own_move),
        opponent_move(gInfo.opponent_move), result(gInfo.result) {}
    GameInfo(const CreatureID& i, const GameMove& ow,
             const GameMove& op, const int res) :
        id(i), own_move(ow), opponent_move(op), result(res) {}
    GameInfo() : id(0), own_move(coop), opponent_move(coop), result(3) {}
};

/*
 *  WorldInfo structure for holding attributes about the
 *  simulated world, including number of different types
 *  of creature, starting resources, and so on.
 */

struct WorldInfo {
    int m_random_strategy;
    int m_tit_for_tat;
    int m_tit_for_two_tats;
    int m_susp_tit_for_tat;
    int m_naive_prober;
    int m_always_cooperate;
    int m_always_defect;
    unsigned int m_starting_creatures;
    unsigned int m_dead_creatures;
    unsigned int m_born_creatures;
    Day m_default_life_expectancy;
    Day m_default_life_expectancy_range;
    Day m_days_to_run;
    int m_default_starting_resources;
    int m_repro_cost;
    int m_repro_min_resources;
    Day m_repro_cycle_days;
    bool m_disable_deaths;
    bool m_disable_repro;

    WorldInfo() :
        m_random_strategy(1), m_tit_for_tat(1),
        m_tit_for_two_tats(1), m_susp_tit_for_tat(1),
        m_naive_prober(1),
        m_always_cooperate(1), m_always_defect(1),
        m_starting_creatures(0), m_dead_creatures(0),
        m_born_creatures(0),
        m_default_life_expectancy(100), m_default_life_expectancy_range(0),
        m_days_to_run(10), m_default_starting_resources(100),
        m_repro_cost(50), m_repro_min_resources(100),
        m_repro_cycle_days(10),
        m_disable_deaths(false), m_disable_repro(false) {}
};

//  Class and struct typedefs

typedef std::list<GameInfo> GameInfoList;
typedef std::map<CreatureID, GameInfoList > GameInfoMap;

}       //  namespace pridil

#endif      // PG_PRIDIL_COMMON_TYPES_H

/*
 *  pridil_common_types.h
 *  =====================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Common types for iterated prisoner's dilemma simulation.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_COMMON_TYPES_H
#define PG_PRIDIL_COMMON_TYPES_H

#include <vector>
#include <map>
#include <list>

//  Simple typedefs

typedef int CreatureID;
typedef int Day;

//  Enumerations

enum GameMove { coop, defect, coop_recip, defect_retal,
                coop_random, defect_random };

enum Strategy { random_strategy, tit_for_tat, susp_tit_for_tat,
                tit_for_two_tats, grudger, naive_prober, remorseful_prober,
                always_cooperate, always_defect };

// Exceptions

class BadGameMove {};
class UnknownStrategy {};
class InvalidOpponentMemory {};

// Structures and classes

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

//  Class and struct typedefs

typedef std::list<GameInfo *> GameInfoList;
typedef std::map<CreatureID, GameInfoList > GameInfoMap;

#endif      // PG_PRIDIL_COMMON_TYPES_H

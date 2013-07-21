// pridil_types.h
// ==============
//
// Copyright 2013 Paul Griffiths
//
// Typedefs for Prisoners' Dilemma simulation

#ifndef PG_PRIDIL_TYPES_H
#define PG_PRIDIL_TYPES_H

#include <vector>
#include <map>
#include <list>

class Creature;     // forward declaration for CreatureList typedef
struct GameInfo;    // forward declaration for GameInfoList typdef

typedef int CreatureID;
typedef int Day;
typedef std::vector<Creature *> CreatureList;
typedef std::list<GameInfo *> GameInfoList;
typedef std::map<CreatureID, GameInfoList > GameInfoMap;

enum GameMove { coop, defect, coop_recip, defect_retal,
                coop_random, defect_random };

enum Strategy { random_strategy, tit_for_tat, susp_tit_for_tat,
                tit_for_two_tats, grudger, naive_prober, remorseful_prober,
                always_cooperate, always_defect };

// Exceptions

class BadGameMove {};
class UnknownStrategy {};

#endif      // PG_PRIDIL_TYPES_H

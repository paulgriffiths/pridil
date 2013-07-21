/*
 *  dna.cpp
 *  =======
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of DNA class for Prisoners' Dilemma simulation.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <string>
#include <cstdlib>

#include "dna.h"
#include "game.h"


/*
 *  DNA class constructor
 *
 *  m_strategy_gene is a pointer, and the associated genes are created
 *  with the new operator, because we need polymorphism via a base
 *  class.
 */

DNA::DNA(Strategy strategy) : m_strategy_gene(0) {
    switch ( strategy ) {
        case tit_for_tat:
            m_strategy_gene = new TitForTatGene();
            break;
        case tit_for_two_tats:
            m_strategy_gene = new TitForTwoTatsGene();
            break;
        case susp_tit_for_tat:
            m_strategy_gene = new SuspTitForTatGene();
            break;
        case naive_prober:
            m_strategy_gene = new NaiveProberGene();
            break;
        case random_strategy:
            m_strategy_gene = new RandomStrategyGene();
            break;
        case always_cooperate:
            m_strategy_gene = new AlwaysCooperateGene();
            break;
        case always_defect:
            m_strategy_gene = new AlwaysDefectGene();
            break;
        default:
            throw UnknownStrategy();
     }
}


/*
 *  DNA destructor, deletes strategy gene
 */

DNA::~DNA() {
    delete m_strategy_gene;
}


/*
 *  Returns the name of the playing strategy contained in DNA
 */

const std::string DNA::strategy() const {
    return m_strategy_gene->name();
}


/*
 *  Gets a game move against a particular opponent.
 *
 *  The DNA object consults its strategy gene to determine the move.
 *
 *  Arguments:
 *    opponent_memory -- a list of the results of previous games with
 *                       a particular opponent. The DNA may, or may not,
 *                       use these memories to decide on its move,
 *                       depending on its particular strategy.
 *
 *  Returns:
 *    A GameMove object representing the move played.
 */

GameMove DNA::get_game_move(GameInfoList& opponent_memory) {
    return m_strategy_gene->get_game_move(opponent_memory);
}


/*
 *  name getter method definitions for strategy genes
 */

std::string RandomStrategyGene::name() const {
    return std::string("random strategy");
}

std::string TitForTatGene::name() const {
    return std::string("tit for tat");
}

std::string TitForTwoTatsGene::name() const {
    return std::string("tit for two tats");
}

std::string SuspTitForTatGene::name() const {
    return std::string("suspicious tit for tat");
}

std::string NaiveProberGene::name() const {
    return std::string("naive prober");
}

std::string AlwaysCooperateGene::name() const {
    return std::string("always cooperate");
}

std::string AlwaysDefectGene::name() const {
    return std::string("always defect");
}


/*
 *  Gets a game move against a particular opponent.
 *
 *  Arguments:
 *    opponent_memory -- a list of the results of previous games with
 *                       a particular opponent. The gene may, or may not,
 *                       use these memories to decide on its move,
 *                       depending on its particular strategy. Each
 *                       individual subclass of StrategyGene has its
 *                       own particular strategy.
 *
 *  Returns:
 *    A GameMove object representing the move played.
 */


/*
 *  TitForTatGene cooperates on its first encounter with a particular
 *  opponent, and thereafter reciprocally cooperates if that opponent
 *  cooperated during the preceding game, and defects in retaliation
 *  if that opponent defected during the preceding game.
 */

GameMove TitForTatGene::get_game_move(GameInfoList& opponent_memory) {
    GameMove my_move;

    if ( opponent_memory.empty() ) {
        my_move = coop;
    } else {
        GameInfo * last_game = opponent_memory.back();
        if ( simplify_game_move(last_game->opponent_move) == defect ) {
            my_move = defect_retal;
        } else {
            my_move = coop_recip;
        }
    }
    return my_move;
}


/*
 *  TitForTwoTatsGene works in the same way as TitForTatGene, except it
 *  will tolerate two defections before retaliating with a defection of
 *  its own. It is therefore nicer than TitForTatGene, which can get caught
 *  in an endless cycle of mutual recriminations (e.g. with a
 *  SuspTitForTatGene).
 */

GameMove TitForTwoTatsGene::get_game_move(GameInfoList& opponent_memory) {
    GameMove my_move;

    if ( opponent_memory.empty() ) {
        my_move = coop;
    } else if ( opponent_memory.size() == 1 ) {
        GameInfo * pgame = opponent_memory.back();

        if ( simplify_game_move(pgame->opponent_move) == coop ) {
            my_move = coop_recip;
        } else {
            my_move = coop;
        }
    } else {
        GameInfoList::const_iterator i = opponent_memory.end();
        GameInfo * pgame = *(--i);
        GameInfo * ppgame = *(--i);

        if ( simplify_game_move(pgame->opponent_move) == defect &&
             simplify_game_move(ppgame->opponent_move) == defect ) {
            my_move = defect_retal;
        } else if ( simplify_game_move(pgame->opponent_move) == defect &&
                    simplify_game_move(ppgame->opponent_move) == coop ) {
            my_move = coop;
        } else {
            my_move = coop_recip;
        }
    }
    return my_move;
}


/*
 *  SuspTitForTatGene works in the same way as TitForTatGene, except on
 *  its first encounter with a particular opponent, it defects rather
 *  than cooperates. SuspTitForTatGene is therefore nastier than
 *  TitForTatGene.
 */

GameMove SuspTitForTatGene::get_game_move(GameInfoList& opponent_memory) {
    GameMove my_move;

    if ( opponent_memory.empty() ) {
        my_move = defect;
    } else {
        GameInfo * last_game = opponent_memory.back();
        if ( simplify_game_move(last_game->opponent_move) == defect ) {
            my_move = defect_retal;
        } else {
            my_move = coop_recip;
        }
    }
    return my_move;
}


/*
 *  NaiveProberGene works in the same way as TitForTatGene, except on
 *  each move there is a random probability (such probability
 *  represented by the m_prob_random_defect member) of it defecting.
 *  It is therefore nastier than TitForTatGene.
 */

GameMove NaiveProberGene::get_game_move(GameInfoList& opponent_memory) {
    GameMove my_move;

    if ( opponent_memory.empty() ) {
        my_move = coop;
    } else {
        GameInfo * last_game = opponent_memory.back();
        if ( simplify_game_move(last_game->opponent_move) == defect ) {
            my_move = defect_retal;
        } else {
            if ( (static_cast<double> (rand()) / RAND_MAX) <
                  m_prob_random_defect ) {
                my_move = defect_random;
            } else {
                my_move = coop_recip;
            }
        }
    }
    return my_move;
}

#pragma GCC diagnostic ignored "-Wunused-parameter"

//  Disable GCC unused-parameter warnings for the following methods, which
//  are virtual. The parameter is needed for these functions in other
//  classes, and are deliberately ignored for these where the strategy
//  is independent of any memories of previous interactions with the
//  opponent creature.


/*
 *  RandomStrategyGene randomly defects 50% of the time, and cooperates
 *  50% of the time, with no regard to memories of previous encounters
 *  with a particular opponent.
 */

GameMove RandomStrategyGene::get_game_move(GameInfoList& opponent_memory) {
    return static_cast<GameMove> (rand() % 2);
}


/*  AlwaysCooperateGene, as the name suggests, always cooperates regardless
 *  of memories of previous encounters with a particular opponent.
 *  Naturally, it is the nicest gene of all.
 */

GameMove AlwaysCooperateGene::get_game_move(GameInfoList& opponent_memory) {
    return coop;
}


/*
 *  AlwaysDefectGene, as the name suggests, always defects regardless of
 *  memories of previous encounters with a particular opponent. Naturally,
 *  it is the nastiest gene of all.
 */

GameMove AlwaysDefectGene::get_game_move(GameInfoList& opponent_memory) {
    return defect;
}

#pragma GCC diagnostic pop

/*
 *  test_tft_vs_tft.cpp
 *  ===================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Pridil unit tests for competitions against creatures.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../../creature.h"
#include "../../game.h"

using namespace pridil;


static void play_game(Creature * creature1, Creature * creature2);

static int mutual_coop_result = 3;
static int mutual_defect_result = -1;
static int sucker_result = -3;
static int victor_result = 5;


TEST_GROUP(CreatureBattleGroup) {
};



/*
 *  Tests that creature resources are as expected after a 5 game run
 *  between two creatures with tit_for_tat strategy.
 *
 *  Expected results are:
 *    1. coop           coop
 *    2. coop_recip     coop_recip
 *    3. coop_recip     coop_recip
 *    4. coop_recip     coop_recip
 *    5. coop_recip     coop_recip
 *
 *  with each creature increasing its starting resources by
 *  mutual_coop_result * 5.
 */

TEST(CreatureBattleGroup, TftVsTftTest) {
    Creature creature1(CreatureInit(1000, 0, tit_for_tat, 100, 50, 75));
    Creature creature2(CreatureInit(1000, 0, tit_for_tat, 100, 50, 75));

    for ( int i = 0; i < 5; ++i ) {
        play_game(&creature1, &creature2);
    }

    int exp_res1 = 100 + mutual_coop_result * 5;
    int exp_res2 = 100 + mutual_coop_result * 5;
    CHECK_EQUAL(exp_res1, creature1.resources());
    CHECK_EQUAL(exp_res2, creature2.resources());
}


/*
 *  Tests that creature resources are as expected after a 5 game run
 *  between a creature with a tit_for_tat strategy, and a creature
 *  with a suspicious_tit_for_tat strategy.
 *
 *  Expected results are:
 *    1. coop           defect
 *    2. defect_retal   coop_recip
 *    3. coop_recip     defect_retal
 *    4. defect_retal   coop_recip
 *    5. coop_recip     defect_retal
 *
 *  with each creature increasing its starting resources by:
 *    1. sucker_result * 3 + victor_result * 2
 *    2. victor_result * 3 + sucker_result * 2
 */

TEST(CreatureBattleGroup, TftVsStftTest) {
    Creature creature1(CreatureInit(1000, 0, tit_for_tat, 100, 50, 75));
    Creature creature2(CreatureInit(1000, 0, susp_tit_for_tat, 100, 50, 75));

    for ( int i = 0; i < 5; ++i ) {
        play_game(&creature1, &creature2);
    }

    int exp_res1 = 100 + sucker_result * 3 + victor_result * 2;
    int exp_res2 = 100 + victor_result * 3 + sucker_result * 2;
    CHECK_EQUAL(exp_res1, creature1.resources());
    CHECK_EQUAL(exp_res2, creature2.resources());
}


/*
 *  Tests that creature resources are as expected after a 5 game run
 *  between a creature with an always_cooperate strategy, and a creature
 *  with an always_defect strategy.
 *
 *  Expected results are:
 *    1. coop           defect
 *    2. coop           defect
 *    3. coop           defect
 *    4. coop           defect
 *    5. coop           defect
 *
 *  with each creature increasing its starting resources by:
 *    1. sucker_result * 5
 *    2. victor_result * 5
 */

TEST(CreatureBattleGroup, AcVsAdTest) {
    Creature creature1(CreatureInit(1000, 0, always_cooperate, 100, 50, 75));
    Creature creature2(CreatureInit(1000, 0, always_defect, 100, 50, 75));

    for ( int i = 0; i < 5; ++i ) {
        play_game(&creature1, &creature2);
    }

    int exp_res1 = 100 + sucker_result * 5;
    int exp_res2 = 100 + victor_result * 5;
    CHECK_EQUAL(exp_res1, creature1.resources());
    CHECK_EQUAL(exp_res2, creature2.resources());
}


/*
 *  Tests that creature resources are as expected after a 5 game run
 *  between a creature with a susp_tit_for_tat strategy, and a creature
 *  with an always_defect strategy.
 *
 *  Expected results are:
 *    1. defect         defect
 *    2. defect_retal   defect
 *    3. defect_retal   defect
 *    4. defect_retal   defect
 *    5. defect_retal   defect
 *
 *  with each creature increasing its starting resources by
 *  mutual_defect * 5
 */

TEST(CreatureBattleGroup, StftVsAdTest) {
    Creature creature1(CreatureInit(1000, 0, susp_tit_for_tat, 100, 50, 75));
    Creature creature2(CreatureInit(1000, 0, always_defect, 100, 50, 75));

    for ( int i = 0; i < 5; ++i ) {
        play_game(&creature1, &creature2);
    }

    int exp_res1 = 100 + mutual_defect_result * 5;
    int exp_res2 = 100 + mutual_defect_result * 5;
    CHECK_EQUAL(exp_res1, creature1.resources());
    CHECK_EQUAL(exp_res2, creature2.resources());
}


/*
 *  Tests that creature resources are as expected after a 5 game run
 *  between a creature with a tit_for_two_tats strategy, and a creature
 *  with a susp_tit_for_tat strategy.
 *
 *  Expected results are:
 *    1. coop           defect
 *    2. coop           coop_recip
 *    3. coop_recip     coop_recip
 *    4. coop_recip     coop_recip
 *    5. coop_recip     coop_recip
 *
 *  with each creature increasing its starting resources by:
 *    1. mutual_coop * 4 + sucker_result * 1
 *    2. mutual_coop * 4 + victor_result * 1
 */

TEST(CreatureBattleGroup, TfttVsStftTest) {
    Creature creature1(CreatureInit(1000, 0, tit_for_two_tats, 100, 50, 75));
    Creature creature2(CreatureInit(1000, 0, susp_tit_for_tat, 100, 50, 75));

    for ( int i = 0; i < 5; ++i ) {
        play_game(&creature1, &creature2);
    }

    int exp_res1 = 100 + mutual_coop_result * 4 + sucker_result;
    int exp_res2 = 100 + mutual_coop_result * 4 + victor_result;
    CHECK_EQUAL(exp_res1, creature1.resources());
    CHECK_EQUAL(exp_res2, creature2.resources());
}


/*
 *  Function plays a game between two creatures.
 *
 *  Each creature is asked for a move, and told the ID of their
 *  opponent so that they can remember previous games with that
 *  opponent. The result of the game is calculated, and each
 *  creature is informed of the result so that they can update
 *  their memories.
 *
 *  Arguments: a pointer to each of the two creatures playing.
 *
 *  Note: duplicated from World::play_game()
 */

static void play_game(Creature * creature1, Creature * creature2) {

    //  Get the move from each of the two creatures

    GameMove c1move = creature1->get_game_move(creature2->id());
    GameMove c2move = creature2->get_game_move(creature1->id());


    //  Populate GameInfo objects for each creature, and
    //  populate with the game result. Simplify the opponent's move
    //  each time, to avoid giving a creature an indication of its
    //  opponent's internal state with regards to game-playing
    //  strategy.

    GameInfo c1info(creature2->id(),
                    c1move,
                    simplify_game_move(c2move),
                    0);
    GameInfo c2info(creature1->id(),
                    c2move,
                    simplify_game_move(c1move),
                    0);
    game_result(c1info, c2info);


    //  Communicate results of the game to each creature

    creature1->give_game_result(c1info);
    creature2->give_game_result(c2info);
}


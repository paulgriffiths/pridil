/*
 *  test_game_result.cpp
 *  ====================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Pridil unit tests for game_result() function.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../../game.h"

using namespace pridil;


static int mutual_coop_result = 3;
static int mutual_defect_result = -1;
static int sucker_result = -3;
static int victor_result = 5;

TEST_GROUP(GameResultGroup) {
};


/*
 *  Test that Nash equilibium and interative requirement hold.
 */

TEST(GameResultGroup, NashTest) {
    CHECK(victor_result > mutual_coop_result);
    CHECK(mutual_coop_result > mutual_defect_result);
    CHECK(mutual_defect_result > sucker_result);
    CHECK((mutual_coop_result * 2) >
          victor_result + sucker_result); 
}


/*
 *  Tests that both players end up with mutual_coop_result
 *  when they both cooperate.
 */

TEST(GameResultGroup, MutualCoopTest) {
    GameInfo gInfo1(0, coop, coop, 0);
    GameInfo gInfo2(1, coop, coop, 0);
    game_result(gInfo1, gInfo2);
    CHECK_EQUAL(gInfo1.result, mutual_coop_result);
    CHECK_EQUAL(gInfo2.result, mutual_coop_result);
}


/*
 *  Tests that both players end up with mutual_defect_result
 *  when they both defect.
 */

TEST(GameResultGroup, MutualDefectTest) {
    GameInfo gInfo1(0, defect, defect, 0);
    GameInfo gInfo2(1, defect, defect, 0);
    game_result(gInfo1, gInfo2);
    CHECK_EQUAL(gInfo1.result, mutual_defect_result);
    CHECK_EQUAL(gInfo2.result, mutual_defect_result);
}


/*
 *  Tests that player 1 ends up with sucker_result, and player 2
 *  ends up with victor_result, when player 1 cooperates and
 *  player 2 defects.
 */

TEST(GameResultGroup, SuckerTest) {
    GameInfo gInfo1(0, coop, defect, 0);
    GameInfo gInfo2(1, defect, coop, 0);
    game_result(gInfo1, gInfo2);
    CHECK_EQUAL(gInfo1.result, sucker_result);
    CHECK_EQUAL(gInfo2.result, victor_result);
}


/*
 *  Tests that player 1 ends up with victor_result, and player 2
 *  ends up with sucker_result, when player 1 defects and
 *  player 2 cooperates.
 */

TEST(GameResultGroup, VictorTest) {
    GameInfo gInfo1(0, defect, coop, 0);
    GameInfo gInfo2(1, coop, defect, 0);
    game_result(gInfo1, gInfo2);
    CHECK_EQUAL(gInfo1.result, victor_result);
    CHECK_EQUAL(gInfo2.result, sucker_result);
}


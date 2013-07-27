/*
 *  test_simplify_game_move.cpp
 *  ===========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Pridil unit tests for simplify_game_move() function.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../../game.h"


TEST_GROUP(SimplifyGameMoveGroup) {
};



/*
 *  Tests that simplify_game_move() appropriately returns
 *  simplified game moves.
 */

TEST(SimplifyGameMoveGroup, SimplyGameMoveTest) {
    GameMove move_coop = coop;
    GameMove move_defect = defect;

    CHECK_EQUAL(simplify_game_move(coop), move_coop);
    CHECK_EQUAL(simplify_game_move(coop_recip), move_coop);
    CHECK_EQUAL(simplify_game_move(coop_random), move_coop);
    CHECK_EQUAL(simplify_game_move(defect), move_defect);
    CHECK_EQUAL(simplify_game_move(defect_retal), move_defect);
    CHECK_EQUAL(simplify_game_move(defect_random), move_defect);
}

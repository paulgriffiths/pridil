/*
 *  test_store_memory.cpp
 *  =====================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Pridil unit tests for stored creature memories.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include <cassert>
#include "../../game.h"
#include "../../memory.h"


TEST_GROUP(StoreMemoryGroup) {
};



/*
 *  Tests that store_memory() correctly populates the memories list,
 *  and that get_memories() returns a list that is the same size as,
 *  and whose members are equal to, a manually constructed check array
 *  of memories.
 */

TEST(StoreMemoryGroup, StoreMemoriesTest) {
    Memory test_memories;
    GameInfoList test_list;
    GameInfo gInfo[8];

    gInfo[0] = GameInfo(1, coop, coop, 0);
    gInfo[1] = GameInfo(1, coop_recip, defect_random, 0);
    gInfo[2] = GameInfo(2, defect, coop, 0);
    gInfo[3] = GameInfo(2, defect, defect_retal, 0);
    gInfo[4] = GameInfo(1, defect_retal, coop_recip, 0);
    gInfo[5] = GameInfo(1, coop_recip, defect_retal, 0);
    gInfo[6] = GameInfo(2, defect, defect_retal, 0);
    gInfo[7] = GameInfo(1, defect_retal, coop_recip, 0);

    for ( int i = 0; i < 8; ++i ) {
        test_memories.store_memory(gInfo[i]);
    }


    //  Tests for opponent id 1

    //  Check memories list is correct size

    int test_size = test_memories.num_memories(1);
    CHECK_EQUAL(test_size, 5);


    //  Check memories list members are as expected

    int n = 5;
    for ( int i = 0; i < 8; ++i ) {
        if ( gInfo[i].id == 2 ) {
            continue;
        }
        CHECK_EQUAL(simplify_game_move(gInfo[i].opponent_move),
                    test_memories.remember_move(1, n--));
    }


    //  Tests for opponent id 2

    //  Check memories list is correct size

    test_size = test_memories.num_memories(2);
    CHECK_EQUAL(test_size, 3);


    //  Check memories list members are as expected

    n = 3;
    for ( int i = 0; i < 8; ++i ) {
        if ( gInfo[i].id == 1 ) {
            continue;
        }
        CHECK_EQUAL(simplify_game_move(gInfo[i].opponent_move),
                    test_memories.remember_move(2, n--));
    }

}

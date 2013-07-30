/*
 *  test_num_memories.cpp
 *  =====================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Pridil unit tests for memory test_num_memories function.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../../brain_complex.h"
#include "../../game.h"

using namespace pridil;


TEST_GROUP(NumMemoriesGroup) {
};



/*
 *  Tests that recognize() correctly returns true for opponents with
 *  existing memories, and returns false for opponents without
 *  existing memories.
 */

TEST(NumMemoriesGroup, NumMemoriesTest) {
    Memory test_memories;
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

    CHECK_EQUAL(test_memories.num_memories(0), 0);
    CHECK_EQUAL(test_memories.num_memories(1), 5);
    CHECK_EQUAL(test_memories.num_memories(2), 3);
    CHECK_EQUAL(test_memories.num_memories(3), 0);
}

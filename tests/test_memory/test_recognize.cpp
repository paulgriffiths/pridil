/*
 *  test_recognize.cpp
 *  ==================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Pridil unit tests for memory creature recognition
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../../game.h"
#include "../../memory.h"


TEST_GROUP(RecognizeMemoryGroup) {
};



/*
 *  Tests that recognize() correctly returns true for opponents with
 *  existing memories, and returns false for opponents without
 *  existing memories.
 */

TEST(RecognizeMemoryGroup, RecognizeOpponentTest) {
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

    CHECK(test_memories.recognize(0) == false);
    CHECK(test_memories.recognize(1));
    CHECK(test_memories.recognize(2));
    CHECK(test_memories.recognize(3) == false);
}

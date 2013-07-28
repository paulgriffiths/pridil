/*
 *
 *  test_alwayscooperategene.cpp
 *  ============================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Pridil unit tests for AlwaysCooperateGene.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../../dna.h"


TEST_GROUP(AlwaysCooperateGeneGroup) {
};



/*
 *  Tests that AlwaysCooperateGene plays 'coop' when it has no memories
 *  of given opponent.
 */

TEST(AlwaysCooperateGeneGroup, CoopOnFirstTest) {
    AlwaysCooperateGene test_gene;
    GameInfoList test_memories;
    GameMove test_response;
    GameMove expected_response = coop;

    test_response = test_gene.get_game_move(0, test_memories);
    CHECK_EQUAL(test_response, expected_response);
}


/*
 *  Tests that AlwaysCooperateGene plays 'coop' when the previous move
 *  of that opponent is 'coop' and the previous move of this gene is
 *  also 'coop'
 */

TEST(AlwaysCooperateGeneGroup, CoopOnGoodMemoryTest) {
    AlwaysCooperateGene test_gene;

    GameInfo gInfo(0, coop, coop, 0);

    GameInfoList test_memories;
    test_memories.push_back(&gInfo);

    GameMove expected_response = coop;
    GameMove test_response = test_gene.get_game_move(0, test_memories);

    CHECK_EQUAL(test_response, expected_response);
}


/*
 *  Tests that AlwaysCooperateGene plays 'coop' when the previous move
 *  of that opponent is 'coop' and the previous move of this gene is
 *  'defect'
 *
 *  Note: as its name suggests, this gene should never actually
 *  play 'defect'.
 */

TEST(AlwaysCooperateGeneGroup, CoopOnGoodMemory2Test) {
    AlwaysCooperateGene test_gene;

    GameInfo gInfo(0, defect, coop, 0);

    GameInfoList test_memories;
    test_memories.push_back(&gInfo);

    GameMove expected_response = coop;
    GameMove test_response = test_gene.get_game_move(0, test_memories);

    CHECK_EQUAL(test_response, expected_response);
}


/*
 *  Tests that AlwaysCooperateGene plays 'coop' when the previous move
 *  of that opponent is 'defect' and the previous move of this gene is
 *  'coop'
 */

TEST(AlwaysCooperateGeneGroup, CoopOnBadMemory1Test) {
    AlwaysCooperateGene test_gene;

    GameInfo gInfo(0, coop, defect, 0);

    GameInfoList test_memories;
    test_memories.push_back(&gInfo);

    GameMove expected_response = coop;
    GameMove test_response = test_gene.get_game_move(0, test_memories);

    CHECK_EQUAL(test_response, expected_response);
}


/*
 *  Tests that AlwaysCooperateGene plays 'coop' when the previous move
 *  of that opponent is 'defect' and the previous move of this gene is
 *  'defect'
 *
 *  Note: as its name suggests, this gene should never actually
 *  play 'defect'.
 */

TEST(AlwaysCooperateGeneGroup, CoopOnBadMemory2Test) {
    AlwaysCooperateGene test_gene;

    GameInfo gInfo(0, defect, defect, 0);

    GameInfoList test_memories;
    test_memories.push_back(&gInfo);

    GameMove expected_response = coop;
    GameMove test_response = test_gene.get_game_move(0, test_memories);

    CHECK_EQUAL(test_response, expected_response);
}


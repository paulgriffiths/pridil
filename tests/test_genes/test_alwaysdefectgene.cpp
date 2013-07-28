/*
 *
 *  test_alwaysdefectgene.cpp
 *  =========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Pridil unit tests for AlwaysDefectGene.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../../dna.h"


TEST_GROUP(AlwaysDefectGeneGroup) {
};



/*
 *  Tests that AlwaysDefectGene plays 'defect' when it has no memories
 *  of given opponent.
 */

TEST(AlwaysDefectGeneGroup, DefectOnFirstTest) {
    AlwaysDefectGene test_gene;
    GameInfoList test_memories;
    GameMove test_response;
    GameMove expected_response = defect;

    test_response = test_gene.get_game_move(0, test_memories);
    CHECK_EQUAL(test_response, expected_response);
}


/*
 *  Tests that AlwaysDefectGene plays 'defect' when the previous move
 *  of that opponent is 'coop' and the previous move of this gene is
 *  also 'coop'
 *
 *  Note: as its name suggests, this gene should never actually
 *  play 'coop'.
 */

TEST(AlwaysDefectGeneGroup, DefectOnGoodMemoryTest) {
    AlwaysDefectGene test_gene;

    GameInfo gInfo(0, coop, coop, 0);

    GameInfoList test_memories;
    test_memories.push_back(&gInfo);

    GameMove expected_response = defect;
    GameMove test_response = test_gene.get_game_move(0, test_memories);

    CHECK_EQUAL(test_response, expected_response);
}


/*
 *  Tests that AlwaysDefectGene plays 'defect' when the previous move
 *  of that opponent is 'coop' and the previous move of this gene is
 *  'defect'
 */

TEST(AlwaysDefectGeneGroup, DefectOnGoodMemory2Test) {
    AlwaysDefectGene test_gene;

    GameInfo gInfo(0, defect, coop, 0);

    GameInfoList test_memories;
    test_memories.push_back(&gInfo);

    GameMove expected_response = defect;
    GameMove test_response = test_gene.get_game_move(0, test_memories);

    CHECK_EQUAL(test_response, expected_response);
}


/*
 *  Tests that AlwaysDefectGene plays 'defect' when the previous move
 *  of that opponent is 'defect' and the previous move of this gene is
 *  'coop'
 *
 *  Note: as its name suggests, this gene should never actually
 *  play 'coop'.
 */

TEST(AlwaysDefectGeneGroup, DefectOnBadMemory1Test) {
    AlwaysDefectGene test_gene;

    GameInfo gInfo(0, coop, defect, 0);

    GameInfoList test_memories;
    test_memories.push_back(&gInfo);

    GameMove expected_response = defect;
    GameMove test_response = test_gene.get_game_move(0, test_memories);

    CHECK_EQUAL(test_response, expected_response);
}


/*
 *  Tests that AlwaysDefectGene plays 'defect' when the previous move
 *  of that opponent is 'defect' and the previous move of this gene is
 *  'defect'
 */

TEST(AlwaysDefectGeneGroup, DefectOnBadMemory2Test) {
    AlwaysDefectGene test_gene;

    GameInfo gInfo(0, defect, defect, 0);

    GameInfoList test_memories;
    test_memories.push_back(&gInfo);

    GameMove expected_response = defect;
    GameMove test_response = test_gene.get_game_move(0, test_memories);

    CHECK_EQUAL(test_response, expected_response);
}


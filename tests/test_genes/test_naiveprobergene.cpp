/*
 *
 *  test_naiveprobergene.cpp
 *  ========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Pridil unit tests for NaiveProberGene.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>

#include <cstdlib>

#include "../../dna.h"


static int time_out;

TEST_GROUP(NaiveProberGeneGroup) {
    void setup() {
        srand((unsigned) time(NULL));
        time_out = 1000;
    }
};



/*
 *  Tests that NaiveProberGene plays 'coop' when it has no memories
 *  of given opponent.
 */

TEST(NaiveProberGeneGroup, CoopOnFirstTest) {
    NaiveProberGene test_gene;
    GameInfoList test_memories;
    GameMove test_response;
    GameMove expected_response = coop;

    test_response = test_gene.get_game_move(test_memories);
    CHECK_EQUAL(test_response, expected_response);
}


/*
 *  Tests that NaiveProberGene eventually plays 'coop_recip' when the
 *  previous move of that opponent is 'coop' and the previous move of
 *  this gene is also 'coop'.
 */

TEST(NaiveProberGeneGroup, CoopOnGoodMemoryTest) {
    NaiveProberGene test_gene;

    GameInfo gInfo(0, coop, coop, 0);

    GameInfoList test_memories;
    test_memories.push_back(&gInfo);

    GameMove expected_response = coop_recip;
    GameMove test_response;
    do {
        test_response = test_gene.get_game_move(test_memories);
    } while ( test_response == defect_random && --time_out > 0 );

    CHECK_EQUAL(test_response, expected_response);
}


/*
 *  Tests that NaiveProberGene eventually plays 'defect_random' when the
 *  previous move of that opponent is 'coop' and the previous move of
 *  this gene is also 'coop'.
 */

TEST(NaiveProberGeneGroup, DefectOnGoodMemoryTest) {
    NaiveProberGene test_gene;

    GameInfo gInfo(0, coop, coop, 0);

    GameInfoList test_memories;
    test_memories.push_back(&gInfo);

    GameMove expected_response = defect_random;
    GameMove test_response;
    do {
        test_response = test_gene.get_game_move(test_memories);
    } while ( test_response == coop_recip && --time_out > 0 );

    CHECK_EQUAL(test_response, expected_response);
}


/*
 *  Tests that NaiveProberGene eventually plays 'coop_recip' when the
 *  previous move of that opponent is 'coop' and the previous move of
 *  this gene is 'defect'
 */

TEST(NaiveProberGeneGroup, CoopOnGoodMemory2Test) {
    NaiveProberGene test_gene;

    GameInfo gInfo(0, defect, coop, 0);

    GameInfoList test_memories;
    test_memories.push_back(&gInfo);

    GameMove expected_response = coop_recip;
    GameMove test_response;
    do {
        test_response = test_gene.get_game_move(test_memories);
    } while ( test_response == defect_random && --time_out > 0 );

    CHECK_EQUAL(test_response, expected_response);
}


/*
 *  Tests that NaiveProberGene eventually plays 'defect_random' when
 *  the previous move of that opponent is 'coop' and the previous move
 *  of this gene is 'defect'
 */

TEST(NaiveProberGeneGroup, DefectOnGoodMemory2Test) {
    NaiveProberGene test_gene;

    GameInfo gInfo(0, defect, coop, 0);

    GameInfoList test_memories;
    test_memories.push_back(&gInfo);

    GameMove expected_response = defect_random;
    GameMove test_response;
    do {
        test_response = test_gene.get_game_move(test_memories);
    } while ( test_response == coop_recip && --time_out > 0 );

    CHECK_EQUAL(test_response, expected_response);
}


/*
 *  Tests that NaiveProberGene plays 'defect_retal' when the previous move
 *  of that opponent is 'defect' and the previous move of this gene is
 *  'coop'
 */

TEST(NaiveProberGeneGroup, DefectOnBadMemory1Test) {
    NaiveProberGene test_gene;

    GameInfo gInfo(0, coop, defect, 0);

    GameInfoList test_memories;
    test_memories.push_back(&gInfo);

    GameMove expected_response = defect_retal;
    GameMove test_response = test_gene.get_game_move(test_memories);

    CHECK_EQUAL(test_response, expected_response);
}


/*
 *  Tests that NaiveProberGene plays 'defect_retal' when the previous move
 *  of that opponent is 'defect' and the previous move of this gene is
 *  'defect'
 */

TEST(NaiveProberGeneGroup, DefectOnBadMemory2Test) {
    NaiveProberGene test_gene;

    GameInfo gInfo(0, defect, defect, 0);

    GameInfoList test_memories;
    test_memories.push_back(&gInfo);

    GameMove expected_response = defect_retal;
    GameMove test_response = test_gene.get_game_move(test_memories);

    CHECK_EQUAL(test_response, expected_response);
}


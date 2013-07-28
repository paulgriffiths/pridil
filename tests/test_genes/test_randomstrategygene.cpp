/*
 *
 *  test_randomstrategygene.cpp
 *  ===========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Pridil unit tests for RandomStrategyGene.
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


TEST_GROUP(RandomStrategyGeneGroup) {
    void setup() {
        srand((unsigned) time(NULL));
        time_out = 1000;
    }
};



/*
 *  Tests that RandomStrategyGene eventually plays 'coop' when it has
 *  no memories of given opponent.
 */

TEST(RandomStrategyGeneGroup, CoopOnFirstTest) {
    RandomStrategyGene test_gene;
    GameInfoList test_memories;
    GameMove test_response;
    GameMove expected_response = coop;

    do {
        test_response = test_gene.get_game_move(0, test_memories);
    } while ( test_response != coop && --time_out > 0 );

    CHECK_EQUAL(test_response, expected_response);
}


/*
 *  Tests that RandomStrategyGene eventually plays 'defect' when it has
 *  no memories of given opponent.
 */

TEST(RandomStrategyGeneGroup, DefectOnFirstTest) {
    RandomStrategyGene test_gene;
    GameInfoList test_memories;
    GameMove test_response;
    GameMove expected_response = defect;

    do {
        test_response = test_gene.get_game_move(0, test_memories);
    } while ( test_response != defect && --time_out > 0 );

    CHECK_EQUAL(test_response, expected_response);
}


/*
 *  Tests that RandomStrategyGene eventually plays 'coop' when the
 *  previous move by this opponent was coop.
 */

TEST(RandomStrategyGeneGroup, CoopOnCoopTest) {
    RandomStrategyGene test_gene;
    GameInfoList test_memories;
    GameInfo gInfo(1, coop, coop, 0);
    test_memories.push_back(&gInfo);
    GameMove test_response;
    GameMove expected_response = coop;

    do {
        test_response = test_gene.get_game_move(1, test_memories);
    } while ( test_response != coop && --time_out > 0 );

    CHECK_EQUAL(test_response, expected_response);
}

/*
 *  Tests that RandomStrategyGene eventually plays 'defect' when the
 *  previous move by this opponent was coop.
 */

TEST(RandomStrategyGeneGroup, DefectOnCoopTest) {
    RandomStrategyGene test_gene;
    GameInfoList test_memories;
    GameInfo gInfo(1, coop, coop, 0);
    test_memories.push_back(&gInfo);
    GameMove test_response;
    GameMove expected_response = defect;

    do {
        test_response = test_gene.get_game_move(1, test_memories);
    } while ( test_response != defect && --time_out > 0 );

    CHECK_EQUAL(test_response, expected_response);
}


/*
 *  Tests that RandomStrategyGene eventually plays 'coop' when the
 *  previous move by this opponent was defect.
 */

TEST(RandomStrategyGeneGroup, CoopOnDefectTest) {
    RandomStrategyGene test_gene;
    GameInfoList test_memories;
    GameInfo gInfo(1, defect, defect, 0);
    test_memories.push_back(&gInfo);
    GameMove test_response;
    GameMove expected_response = coop;

    do {
        test_response = test_gene.get_game_move(1, test_memories);
    } while ( test_response != coop && --time_out > 0 );

    CHECK_EQUAL(test_response, expected_response);
}

/*
 *  Tests that RandomStrategyGene eventually plays 'defect' when the
 *  previous move by this opponent was defect.
 */

TEST(RandomStrategyGeneGroup, DefectOnDefectTest) {
    RandomStrategyGene test_gene;
    GameInfoList test_memories;
    GameInfo gInfo(1, defect, defect, 0);
    test_memories.push_back(&gInfo);
    GameMove test_response;
    GameMove expected_response = defect;

    do {
        test_response = test_gene.get_game_move(1, test_memories);
    } while ( test_response != defect && --time_out > 0 );

    CHECK_EQUAL(test_response, expected_response);
}


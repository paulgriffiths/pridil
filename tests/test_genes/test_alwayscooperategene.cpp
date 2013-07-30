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
#include "../../genes.h"
#include "../../brain_complex.h"


TEST_GROUP(AlwaysCooperateGeneGroup) {
};



/*
 *  Tests that AlwaysCooperateGene plays 'coop' when it has no memories
 *  of given opponent.
 */

TEST(AlwaysCooperateGeneGroup, CoopOnFirstTest) {
    Brain brain(always_cooperate);
    AlwaysCooperateGene test_gene(brain);
    GameMove test_response;
    GameMove expected_response = coop;

    test_response = test_gene.get_game_move(0);
    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that AlwaysCooperateGene plays 'coop' when the previous move
 *  of that opponent is 'coop' and the previous move of this gene is
 *  also 'coop'
 */

TEST(AlwaysCooperateGeneGroup, CoopOnGoodMemoryTest) {
    Brain brain(always_cooperate);
    AlwaysCooperateGene test_gene(brain);

    GameInfo gInfo(0, coop, coop, 0);

    brain.store_memory(gInfo);

    GameMove expected_response = coop;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
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
    Brain brain(always_cooperate);
    AlwaysCooperateGene test_gene(brain);

    GameInfo gInfo(0, defect, coop, 0);

    brain.store_memory(gInfo);

    GameMove expected_response = coop;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that AlwaysCooperateGene plays 'coop' when the previous move
 *  of that opponent is 'defect' and the previous move of this gene is
 *  'coop'
 */

TEST(AlwaysCooperateGeneGroup, CoopOnBadMemory1Test) {
    Brain brain(always_cooperate);
    AlwaysCooperateGene test_gene(brain);

    GameInfo gInfo(0, coop, defect, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = coop;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
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
    Brain brain(always_cooperate);
    AlwaysCooperateGene test_gene(brain);

    GameInfo gInfo(0, defect, defect, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = coop;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
}


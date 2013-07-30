/*
 *
 *  test_titfortatgene.cpp
 *  ======================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Pridil unit tests for TitForTatGene
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../../genes.h"
#include "../../brain_complex.h"

using namespace pridil;


TEST_GROUP(TitForTatGeneGroup) {
};



/*
 *  Tests that TitForTatGene plays 'coop' when it has no memories
 *  of given opponent.
 */

TEST(TitForTatGeneGroup, CoopOnFirstTest) {
    Brain brain(tit_for_tat);
    TitForTatGene test_gene(brain);

    GameMove test_response;
    GameMove expected_response = coop;

    test_response = test_gene.get_game_move(0);
    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that TitForTatGene plays 'coop_recip' when the previous move
 *  of that opponent is 'coop' and the previous move of this gene is
 *  also 'coop'
 */

TEST(TitForTatGeneGroup, CoopOnGoodMemoryTest) {
    Brain brain(tit_for_tat);
    TitForTatGene test_gene(brain);

    GameInfo gInfo(0, coop, coop, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = coop_recip;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that TitForTatGene plays 'coop_recip' when the previous move
 *  of that opponent is 'coop' and the previous move of this gene is
 *  'defect'
 */

TEST(TitForTatGeneGroup, CoopOnGoodMemory2Test) {
    Brain brain(tit_for_tat);
    TitForTatGene test_gene(brain);

    GameInfo gInfo(0, defect, coop, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = coop_recip;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that TitForTatGene plays 'defect_retal' when the previous move
 *  of that opponent is 'defect' and the previous move of this gene is
 *  'coop'
 */

TEST(TitForTatGeneGroup, DefectOnBadMemory1Test) {
    Brain brain(tit_for_tat);
    TitForTatGene test_gene(brain);

    GameInfo gInfo(0, coop, defect, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = defect_retal;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that TitForTatGene plays 'defect_retal' when the previous move
 *  of that opponent is 'defect' and the previous move of this gene is
 *  'defect'
 */

TEST(TitForTatGeneGroup, DefectOnBadMemory2Test) {
    Brain brain(tit_for_tat);
    TitForTatGene test_gene(brain);

    GameInfo gInfo(0, defect, defect, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = defect_retal;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  test_susptitfortatgene.cpp
 *  ==========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Pridil unit tests for SuspTitForTatGene
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


TEST_GROUP(SuspTitForTatGeneGroup) {
};



/*
 *  Tests that SuspTitForTatGene plays 'defect' when it has no memories
 *  of given opponent.
 */

TEST(SuspTitForTatGeneGroup, DefectOnFirstTest) {
    Brain brain(CreatureInit(0, 0, susp_tit_for_tat, 0, 0, 0));
    SuspTitForTatGene test_gene(brain);

    GameMove test_response;
    GameMove expected_response = defect;

    test_response = test_gene.get_game_move(0);
    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that SuspTitForTatGene plays 'coop_recip' when the previous move
 *  of that opponent is 'coop' and the previous move of this gene is
 *  also 'coop'
 */

TEST(SuspTitForTatGeneGroup, CoopOnGoodMemoryTest) {
    Brain brain(CreatureInit(0, 0, susp_tit_for_tat, 0, 0, 0));
    SuspTitForTatGene test_gene(brain);

    GameInfo gInfo(0, coop, coop, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = coop_recip;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that SuspTitForTatGene plays 'coop_recip' when the previous move
 *  of that opponent is 'coop' and the previous move of this gene is
 *  'defect'
 */

TEST(SuspTitForTatGeneGroup, CoopOnGoodMemory2Test) {
    Brain brain(CreatureInit(0, 0, susp_tit_for_tat, 0, 0, 0));
    SuspTitForTatGene test_gene(brain);

    GameInfo gInfo(0, defect, coop, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = coop_recip;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that SuspTitForTatGene plays 'defect_retal' when the previous move
 *  of that opponent is 'defect' and the previous move of this gene is
 *  'coop'
 */

TEST(SuspTitForTatGeneGroup, DefectOnBadMemory1Test) {
    Brain brain(CreatureInit(0, 0, susp_tit_for_tat, 0, 0, 0));
    SuspTitForTatGene test_gene(brain);

    GameInfo gInfo(0, coop, defect, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = defect_retal;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that SuspTitForTatGene plays 'defect_retal' when the previous move
 *  of that opponent is 'defect' and the previous move of this gene is
 *  'defect'
 */

TEST(SuspTitForTatGeneGroup, DefectOnBadMemory2Test) {
    Brain brain(CreatureInit(0, 0, susp_tit_for_tat, 0, 0, 0));
    SuspTitForTatGene test_gene(brain);

    GameInfo gInfo(0, defect, defect, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = defect_retal;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
}


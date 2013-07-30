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
#include "../../genes.h"
#include "../../brain_complex.h"

using namespace pridil;


TEST_GROUP(AlwaysDefectGeneGroup) {
};



/*
 *  Tests that AlwaysDefectGene plays 'defect' when it has no memories
 *  of given opponent.
 */

TEST(AlwaysDefectGeneGroup, DefectOnFirstTest) {
    Brain brain(always_defect);
    AlwaysDefectGene test_gene(brain);

    GameMove test_response;
    GameMove expected_response = defect;

    test_response = test_gene.get_game_move(0);
    CHECK_EQUAL(expected_response, test_response);
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
    Brain brain(always_defect);
    AlwaysDefectGene test_gene(brain);

    GameInfo gInfo(0, coop, coop, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = defect;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that AlwaysDefectGene plays 'defect' when the previous move
 *  of that opponent is 'coop' and the previous move of this gene is
 *  'defect'
 */

TEST(AlwaysDefectGeneGroup, DefectOnGoodMemory2Test) {
    Brain brain(always_defect);
    AlwaysDefectGene test_gene(brain);

    GameInfo gInfo(0, defect, coop, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = defect;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
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
    Brain brain(always_defect);
    AlwaysDefectGene test_gene(brain);

    GameInfo gInfo(0, coop, defect, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = defect;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that AlwaysDefectGene plays 'defect' when the previous move
 *  of that opponent is 'defect' and the previous move of this gene is
 *  'defect'
 */

TEST(AlwaysDefectGeneGroup, DefectOnBadMemory2Test) {
    Brain brain(always_defect);
    AlwaysDefectGene test_gene(brain);

    GameInfo gInfo(0, defect, defect, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = defect;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
}


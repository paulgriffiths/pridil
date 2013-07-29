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
#include "../../brain.h"


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
    Brain brain(naive_prober);
    NaiveProberGene test_gene(brain);

    GameMove test_response;
    GameMove expected_response = coop;

    test_response = test_gene.get_game_move(0);
    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that NaiveProberGene eventually plays 'coop_recip' when the
 *  previous move of that opponent is 'coop' and the previous move of
 *  this gene is also 'coop'.
 */

TEST(NaiveProberGeneGroup, CoopOnGoodMemoryTest) {
    Brain brain(naive_prober);
    NaiveProberGene test_gene(brain);

    GameInfo gInfo(0, coop, coop, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = coop_recip;
    GameMove test_response;
    do {
        test_response = test_gene.get_game_move(0);
    } while ( test_response == defect_random && --time_out > 0 );

    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that NaiveProberGene eventually plays 'defect_random' when the
 *  previous move of that opponent is 'coop' and the previous move of
 *  this gene is also 'coop'.
 */

TEST(NaiveProberGeneGroup, DefectOnGoodMemoryTest) {
    Brain brain(naive_prober);
    NaiveProberGene test_gene(brain);

    GameInfo gInfo(0, coop, coop, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = defect_random;
    GameMove test_response;
    do {
        test_response = test_gene.get_game_move(0);
    } while ( test_response == coop_recip && --time_out > 0 );

    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that NaiveProberGene eventually plays 'coop_recip' when the
 *  previous move of that opponent is 'coop' and the previous move of
 *  this gene is 'defect'
 */

TEST(NaiveProberGeneGroup, CoopOnGoodMemory2Test) {
    Brain brain(naive_prober);
    NaiveProberGene test_gene(brain);

    GameInfo gInfo(0, defect, coop, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = coop_recip;
    GameMove test_response;
    do {
        test_response = test_gene.get_game_move(0);
    } while ( test_response == defect_random && --time_out > 0 );

    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that NaiveProberGene eventually plays 'defect_random' when
 *  the previous move of that opponent is 'coop' and the previous move
 *  of this gene is 'defect'
 */

TEST(NaiveProberGeneGroup, DefectOnGoodMemory2Test) {
    Brain brain(naive_prober);
    NaiveProberGene test_gene(brain);

    GameInfo gInfo(0, defect, coop, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = defect_random;
    GameMove test_response;
    do {
        test_response = test_gene.get_game_move(0);
    } while ( test_response == coop_recip && --time_out > 0 );

    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that NaiveProberGene plays 'defect_retal' when the previous move
 *  of that opponent is 'defect' and the previous move of this gene is
 *  'coop'
 */

TEST(NaiveProberGeneGroup, DefectOnBadMemory1Test) {
    Brain brain(naive_prober);
    NaiveProberGene test_gene(brain);

    GameInfo gInfo(0, coop, defect, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = defect_retal;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that NaiveProberGene plays 'defect_retal' when the previous move
 *  of that opponent is 'defect' and the previous move of this gene is
 *  'defect'
 */

TEST(NaiveProberGeneGroup, DefectOnBadMemory2Test) {
    Brain brain(naive_prober);
    NaiveProberGene test_gene(brain);

    GameInfo gInfo(0, defect, defect, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = defect_retal;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  test_titfortwotatsgene.cpp
 *  ==========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Pridil unit tests for TitForTwoTatsGene
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


TEST_GROUP(TitForTwoTatsGeneGroup) {
};



/*
 *  Tests that TitForTwoTatsGene plays 'coop' when it has no memories
 *  of given opponent.
 */

TEST(TitForTwoTatsGeneGroup, CoopOnFirstTest) {
    Brain brain(CreatureInit(0, 0, tit_for_two_tats, 0, 0, 0));
    TitForTwoTatsGene test_gene(brain);

    GameMove test_response;
    GameMove expected_response = coop;

    test_response = test_gene.get_game_move(0);
    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that TitForTwoTatsGene plays 'coop_recip' when the previous move
 *  of that opponent is 'coop'.
 */

TEST(TitForTwoTatsGeneGroup, CoopOnGoodLastMemoryTest) {
    Brain brain(CreatureInit(0, 0, tit_for_two_tats, 0, 0, 0));
    TitForTwoTatsGene test_gene(brain);

    GameInfo gInfo(0, coop, coop, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = coop_recip;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that TitForTwoTatsGene plays 'coop' when the previous move
 *  of that opponent is 'defect', and there is only one previous memory.
 */

TEST(TitForTwoTatsGeneGroup, CoopOnBadFirstMemoryTest) {
    Brain brain(CreatureInit(0, 0, tit_for_two_tats, 0, 0, 0));
    TitForTwoTatsGene test_gene(brain);

    GameInfo gInfo(0, coop, defect, 0);
    brain.store_memory(gInfo);

    GameMove expected_response = coop;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that TitForTwoTatsGene plays 'coop' when the previous move
 *  of that opponent is 'defect', but the move before that is 'coop'.
 */

TEST(TitForTwoTatsGeneGroup, CoopOnCoopDefectTest) {
    Brain brain(CreatureInit(0, 0, tit_for_two_tats, 0, 0, 0));
    TitForTwoTatsGene test_gene(brain);

    GameInfo gInfo1(0, coop, coop, 0);
    brain.store_memory(gInfo1);
    GameInfo gInfo2(0, coop_recip, defect, 0);
    brain.store_memory(gInfo2);

    GameMove expected_response = coop;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that TitForTwoTatsGene plays 'defect_retal' when the last two
 *  moves of that opponent are 'defect'.
 */

TEST(TitForTwoTatsGeneGroup, DefectOnTwoDefectsTest) {
    Brain brain(CreatureInit(0, 0, tit_for_two_tats, 0, 0, 0));
    TitForTwoTatsGene test_gene(brain);

    GameInfo gInfo1(0, coop, coop, 0);
    brain.store_memory(gInfo1);
    GameInfo gInfo2(0, coop_recip, defect, 0);
    brain.store_memory(gInfo2);
    GameInfo gInfo3(0, coop, defect, 0);
    brain.store_memory(gInfo3);

    GameMove expected_response = defect_retal;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
}


/*
 *  Tests that TitForTwoTatsGene plays 'coop_recip' immediately after
 *  a retalitary defect if the opponent again cooperates.
 */

TEST(TitForTwoTatsGeneGroup, CoopAfterDefectTest) {
    Brain brain(CreatureInit(0, 0, tit_for_two_tats, 0, 0, 0));
    TitForTwoTatsGene test_gene(brain);

    GameInfo gInfo1(0, coop, coop, 0);
    brain.store_memory(gInfo1);
    GameInfo gInfo2(0, coop_recip, defect, 0);
    brain.store_memory(gInfo2);
    GameInfo gInfo3(0, coop, defect, 0);
    brain.store_memory(gInfo3);
    GameInfo gInfo4(0, defect_retal, coop, 0);
    brain.store_memory(gInfo4);

    GameMove expected_response = coop_recip;
    GameMove test_response = test_gene.get_game_move(0);

    CHECK_EQUAL(expected_response, test_response);
}

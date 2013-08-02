/*
 *  test_reproduce.cpp
 *  ==================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Pridil unit tests for Creature reproduction.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../../creature.h"
#include "../../game.h"

using namespace pridil;


TEST_GROUP(CreatureReproduceGroup) {
};



/*
 *  Tests that creature reproduction properly succeeds.
 */

TEST(CreatureReproduceGroup, DoReproduceTest) {
    Creature parent(CreatureInit(100, 0, tit_for_tat, 120, 66, 88));
    
    Creature * child = parent.reproduce();

    CHECK(child != NULL);
    CHECK_EQUAL(66, child->resources());
    CHECK_EQUAL(0, child->age());
    CHECK_EQUAL(tit_for_tat, child->strategy_value());
    CHECK_EQUAL(54, parent.resources());

    delete child;
}


/*
 *  Tests that creature reproduction properly fails.
 */

TEST(CreatureReproduceGroup, DontReproduceTest) {
    Creature parent(CreatureInit(100, 0, tit_for_tat, 120, 66, 130));
    
    Creature * child = parent.reproduce();

    CHECK(child == NULL);
    CHECK_EQUAL(120, parent.resources());

    delete child;
}

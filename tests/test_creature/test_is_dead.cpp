/*
 *  test_is_dead.cpp
 *  ================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Pridil unit tests for Creature death.
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


TEST_GROUP(CreatureDeathGroup) {
};



/*
 *  Tests that creature death properly succeeds and fails due to lack of
 *  resources
 */

TEST(CreatureDeathGroup, DieResourcesTest) {
    Creature creature1(CreatureInit(100, 0, tit_for_tat, 0, 66, 88));
    CHECK(creature1.is_dead());

    Creature creature2(CreatureInit(100, 0, tit_for_tat, 100, 66, 88));
    CHECK(creature2.is_dead() == false);
}


/*
 *  Tests that creature death properly succeeds and fails due to age
 */

TEST(CreatureDeathGroup, DieAgeTest) {
    Creature creature(CreatureInit(5, 0, tit_for_tat, 100, 66, 88));
    
    int n = 5;
    while ( n-- > 0 ) {
        creature.age_day();
    }

    CHECK(creature.is_dead() == false);

    creature.age_day();

    CHECK(creature.is_dead());
}


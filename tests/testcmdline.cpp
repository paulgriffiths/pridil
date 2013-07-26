/*
 *
 *  testcmdline.cpp
 *  ===============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  CmdLineOptions class unit tests.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../cmdline.h"

TEST_GROUP(mygroup) {
};


/*
 *  Tests that cmdline::BadOptionValue is thrown when a non-numeric
 *  integer option is passed, e.g. "-tY" instead of "-t5".
 */

TEST(mygroup, BadIntOptTest) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "-tY"};

    cmdline::CmdLineOptions clopt;
    clopt.set_intopt("test", "-t", "--t", "test desc", false, 0);

    try {
       clopt.parse(t_argc, t_argv);
       FAIL("Exception not thrown on bad intopt provided");
    }
    catch ( cmdline::BadOptionValue ) {

        /*  Test succeeds if we get here  */

    }
    catch (...) {
        FAIL("Wrong exception thrown on bad intopt provided");
    } 
}


/*
 *  Tests that cmdline::MissingOptionValue is thrown when an empty
 *  integer option is passed, e.g. "-t" instead of "-t5".
 */

TEST(mygroup, MissingIntOptTest) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "-t"};

    cmdline::CmdLineOptions clopt;
    clopt.set_intopt("test", "-t", "--t", "test desc", false, 0);

    try {
       clopt.parse(t_argc, t_argv);
       FAIL("Exception not thrown on missing intopt value");
    }
    catch ( cmdline::MissingOptionValue ) {

        /*  Test succeeds if we get here  */

    }
    catch (...) {
        FAIL("Wrong exception thrown on missing intopt value");
    } 
}

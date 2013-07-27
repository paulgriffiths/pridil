/*
 *
 *  test_cmdline_intopt.cpp
 *  =======================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  CmdLineOptions class unit tests for integer options.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../cmdline.h"

TEST_GROUP(IntOptGroup) {
};


/*
 *  Tests that cmdline::BadOptionValue is thrown when a non-numeric
 *  integer option is passed, e.g. "-tY" instead of "-t5".
 */

TEST(IntOptGroup, BadIntOptTest) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "-tY", NULL};

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
 *  Tests that cmdline::BadOptionValue is thrown when a non-numeric
 *  integer option is passed, e.g. "--testY" instead of "--test5".
 */

TEST(IntOptGroup, BadIntOptTest2) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "--testY", NULL};

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
 *  Tests that cmdline::BadOptionValue is thrown when a non-numeric
 *  integer option is passed, e.g. "-t=Y" instead of "-t=5".
 */

TEST(IntOptGroup, BadIntOptTest3) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "-t=Y", NULL};

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
 *  Tests that cmdline::BadOptionValue is thrown when a non-numeric
 *  integer option is passed, e.g. "--test=Y" instead of "--test=5".
 */

TEST(IntOptGroup, BadIntOptTest4) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "--test=Y", NULL};

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

TEST(IntOptGroup, MissingIntOptTest) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "-t", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_intopt("test", "-t", "--test", "test desc", false, 0);

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


/*
 *  Tests that cmdline::MissingOptionValue is thrown when an empty
 *  integer option is passed, e.g. "-t=" instead of "-t=5".
 */

TEST(IntOptGroup, MissingIntOptTest2) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "-t=", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_intopt("test", "-t", "--test", "test desc", false, 0);

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


/*
 *  Tests that cmdline::MissingOptionValue is thrown when an empty
 *  integer option is passed, e.g. "--test" instead of "--test5".
 */

TEST(IntOptGroup, MissingIntOptTest3) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "--test", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_intopt("test", "-t", "--test", "test desc", false, 0);

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


/*
 *  Tests that cmdline::MissingOptionValue is thrown when an empty
 *  integer option is passed, e.g. "--test=" instead of "--test=5".
 */

TEST(IntOptGroup, MissingIntOptTest4) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "--test=", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_intopt("test", "-t", "--test", "test desc", false, 0);

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

/*
 *
 *  test_cmdline_stropt.cpp
 *  =======================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  CmdLineOptions class unit tests for string options.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../cmdline.h"

TEST_GROUP(StrOptGroup) {
};


/*
 *  Tests that cmdline::MissingOptionValue is thrown when an empty
 *  string option is passed, e.g. "-t" instead of "-tfoo".
 */

TEST(StrOptGroup, MissingStrOptTest) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "-t", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_stropt("test", "-t", "--test", "test desc", false, "");

    try {
       clopt.parse(t_argc, t_argv);
       FAIL("Exception not thrown on missing stropt value");
    }
    catch ( cmdline::MissingOptionValue ) {

        /*  Test succeeds if we get here  */

    }
    catch (...) {
        FAIL("Wrong exception thrown on missing stropt value");
    } 
}


/*
 *  Tests that cmdline::MissingOptionValue is thrown when an empty
 *  string option is passed, e.g. "-t=" instead of "-t=foo".
 */

TEST(StrOptGroup, MissingStrOptTest2) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "-t=", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_stropt("test", "-t", "--test", "test desc", false, "");

    try {
       clopt.parse(t_argc, t_argv);
       FAIL("Exception not thrown on missing stropt value");
    }
    catch ( cmdline::MissingOptionValue ) {

        /*  Test succeeds if we get here  */

    }
    catch (...) {
        FAIL("Wrong exception thrown on missing stropt value");
    } 
}


/*
 *  Tests that cmdline::MissingOptionValue is thrown when an empty
 *  string option is passed, e.g. "--test" instead of "--testfoo".
 */

TEST(StrOptGroup, MissingStrOptTest3) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "--test", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_stropt("test", "-t", "--test", "test desc", false, "");

    try {
       clopt.parse(t_argc, t_argv);
       FAIL("Exception not thrown on missing stropt value");
    }
    catch ( cmdline::MissingOptionValue ) {

        /*  Test succeeds if we get here  */

    }
    catch (...) {
        FAIL("Wrong exception thrown on missing stropt value");
    } 
}


/*
 *  Tests that cmdline::MissingOptionValue is thrown when an empty
 *  string option is passed, e.g. "--test=" instead of "--test=foo".
 */

TEST(StrOptGroup, MissingStrOptTest4) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "--test=", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_stropt("test", "-t", "--test", "test desc", false, "");

    try {
       clopt.parse(t_argc, t_argv);
       FAIL("Exception not thrown on missing stropt value");
    }
    catch ( cmdline::MissingOptionValue ) {

        /*  Test succeeds if we get here  */

    }
    catch (...) {
        FAIL("Wrong exception thrown on missing stropt value");
    } 
}

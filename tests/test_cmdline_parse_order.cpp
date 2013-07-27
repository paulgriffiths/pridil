/*
 *
 *  test_cmdline_parse_order.cpp
 *  ============================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  CmdLineOptions class unit tests for parse() order exceptions.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../cmdline.h"


TEST_GROUP(ParseOrderGroup) {
};


/*
 *  Tests that cmdline::ParseNotCalled is thrown when calling
 *  is_flag_set() prior to calling parse()
 */

TEST(ParseOrderGroup, IsFlagSetBeforeParse) {
    cmdline::CmdLineOptions clopt;

    try {
       clopt.is_flag_set("-t");
       FAIL("Exception not thrown");
    }
    catch ( cmdline::ParseNotCalled ) {

        /*  Test succeeds if we get here  */

    }
    catch (...) {
        FAIL("Wrong exception thrown");
    } 
}


/*
 *  Tests that cmdline::ParseNotCalled is thrown when calling
 *  is_intopt_set() prior to calling parse()
 */

TEST(ParseOrderGroup, IsIntoptSetBeforeParse) {
    cmdline::CmdLineOptions clopt;

    try {
       clopt.is_intopt_set("-t");
       FAIL("Exception not thrown");
    }
    catch ( cmdline::ParseNotCalled ) {

        /*  Test succeeds if we get here  */

    }
    catch (...) {
        FAIL("Wrong exception thrown");
    } 
}


/*
 *  Tests that cmdline::ParseNotCalled is thrown when calling
 *  is_stropt_set() prior to calling parse()
 */

TEST(ParseOrderGroup, IsStroptSetBeforeParse) {
    cmdline::CmdLineOptions clopt;

    try {
       clopt.is_stropt_set("-t");
       FAIL("Exception not thrown");
    }
    catch ( cmdline::ParseNotCalled ) {

        /*  Test succeeds if we get here  */

    }
    catch (...) {
        FAIL("Wrong exception thrown");
    } 
}


/*
 *  Tests that cmdline::ParseNotCalled is thrown when calling
 *  is_posarg_set() prior to calling parse()
 */

TEST(ParseOrderGroup, IsPosargSetBeforeParse) {
    cmdline::CmdLineOptions clopt;

    try {
       clopt.is_posarg_set("-t");
       FAIL("Exception not thrown");
    }
    catch ( cmdline::ParseNotCalled ) {

        /*  Test succeeds if we get here  */

    }
    catch (...) {
        FAIL("Wrong exception thrown");
    } 
}


/*
 *  Tests that cmdline::ParseNotCalled is thrown when calling
 *  get_intopt_value() prior to calling parse()
 */

TEST(ParseOrderGroup, GetIntoptValueBeforeParse) {
    cmdline::CmdLineOptions clopt;

    try {
       clopt.get_intopt_value("-t");
       FAIL("Exception not thrown");
    }
    catch ( cmdline::ParseNotCalled ) {

        /*  Test succeeds if we get here  */

    }
    catch (...) {
        FAIL("Wrong exception thrown");
    } 
}


/*
 *  Tests that cmdline::ParseNotCalled is thrown when calling
 *  get_stropt_value() prior to calling parse()
 */

TEST(ParseOrderGroup, GetStroptValueBeforeParse) {
    cmdline::CmdLineOptions clopt;

    try {
       clopt.get_stropt_value("-t");
       FAIL("Exception not thrown");
    }
    catch ( cmdline::ParseNotCalled ) {

        /*  Test succeeds if we get here  */

    }
    catch (...) {
        FAIL("Wrong exception thrown");
    } 
}


/*
 *  Tests that cmdline::ParseNotCalled is thrown when calling
 *  get_pos_args() prior to calling parse()
 */

TEST(ParseOrderGroup, GetPosargsBeforeParse) {
    cmdline::CmdLineOptions clopt;

    try {
       clopt.get_pos_args();
       FAIL("Exception not thrown");
    }
    catch ( cmdline::ParseNotCalled ) {

        /*  Test succeeds if we get here  */

    }
    catch (...) {
        FAIL("Wrong exception thrown");
    } 
}


/*
 *  Tests that cmdline::ParseAlreadyCalled is thrown when calling
 *  set_program_name() after calling parse()
 */

TEST(ParseOrderGroup, SetProgramNameAfterParse) {
    int t_argc = 1;
    const char * t_argv[] = {"pridil", NULL};
    cmdline::CmdLineOptions clopt;
    clopt.parse(t_argc, t_argv);

    try {
        clopt.set_program_name("test");
        FAIL("Exception not thrown");
    }
    catch ( cmdline::ParseAlreadyCalled ) {

        /*  Test succeeds if we get here  */

    }
    catch (...) {
        FAIL("Wrong exception thrown");
    } 
}


/*
 *  Tests that cmdline::ParseAlreadyCalled is thrown when calling
 *  set_version_number() after calling parse()
 */

TEST(ParseOrderGroup, SetVersionNumberAfterParse) {
    int t_argc = 1;
    const char * t_argv[] = {"pridil", NULL};
    cmdline::CmdLineOptions clopt;
    clopt.parse(t_argc, t_argv);

    try {
        clopt.set_version_number("test");
        FAIL("Exception not thrown");
    }
    catch ( cmdline::ParseAlreadyCalled ) {

        /*  Test succeeds if we get here  */

    }
    catch (...) {
        FAIL("Wrong exception thrown");
    } 
}


/*
 *  Tests that cmdline::ParseAlreadyCalled is thrown when calling
 *  set_config_file_option() after calling parse()
 */

TEST(ParseOrderGroup, SetConfigFileOptionAfterParse) {
    int t_argc = 1;
    const char * t_argv[] = {"pridil", NULL};
    cmdline::CmdLineOptions clopt;
    clopt.parse(t_argc, t_argv);

    try {
        clopt.set_config_file_option("test");
        FAIL("Exception not thrown");
    }
    catch ( cmdline::ParseAlreadyCalled ) {

        /*  Test succeeds if we get here  */

    }
    catch (...) {
        FAIL("Wrong exception thrown");
    } 
}


/*
 *  Tests that cmdline::ParseAlreadyCalled is thrown when calling
 *  set_intopt() after calling parse()
 */

TEST(ParseOrderGroup, SetIntOptAfterParse) {
    int t_argc = 1;
    const char * t_argv[] = {"pridil", NULL};
    cmdline::CmdLineOptions clopt;
    clopt.parse(t_argc, t_argv);

    try {
        clopt.set_intopt("test", "-t", "-t", "test desc", false, 0);
        FAIL("Exception not thrown");
    }
    catch ( cmdline::ParseAlreadyCalled ) {

        /*  Test succeeds if we get here  */

    }
    catch (...) {
        FAIL("Wrong exception thrown");
    } 
}


/*
 *  Tests that cmdline::ParseAlreadyCalled is thrown when calling
 *  set_stropt() after calling parse()
 */

TEST(ParseOrderGroup, SetStrOptAfterParse) {
    int t_argc = 1;
    const char * t_argv[] = {"pridil", NULL};
    cmdline::CmdLineOptions clopt;
    clopt.parse(t_argc, t_argv);

    try {
        clopt.set_stropt("test", "-t", "-t", "test desc", false, "");
        FAIL("Exception not thrown");
    }
    catch ( cmdline::ParseAlreadyCalled ) {

        /*  Test succeeds if we get here  */

    }
    catch (...) {
        FAIL("Wrong exception thrown");
    } 
}


/*
 *  Tests that cmdline::ParseAlreadyCalled is thrown when calling
 *  set_flag() after calling parse()
 */

TEST(ParseOrderGroup, SetFlagAfterParse) {
    int t_argc = 1;
    const char * t_argv[] = {"pridil", NULL};
    cmdline::CmdLineOptions clopt;
    clopt.parse(t_argc, t_argv);

    try {
        clopt.set_flag("test", "-t", "-t", "test desc", false);
        FAIL("Exception not thrown");
    }
    catch ( cmdline::ParseAlreadyCalled ) {

        /*  Test succeeds if we get here  */

    }
    catch (...) {
        FAIL("Wrong exception thrown");
    } 
}

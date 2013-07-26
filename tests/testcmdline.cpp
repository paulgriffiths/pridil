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
 *  Tests that cmdline::BadOptionValue is thrown when a non-numeric
 *  integer option is passed, e.g. "--testY" instead of "--test5".
 */

TEST(mygroup, BadIntOptTest2) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "--testY"};

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

TEST(mygroup, BadIntOptTest3) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "-t=Y"};

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

TEST(mygroup, BadIntOptTest4) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "--test=Y"};

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

TEST(mygroup, MissingIntOptTest2) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "-t="};

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

TEST(mygroup, MissingIntOptTest3) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "--test"};

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

TEST(mygroup, MissingIntOptTest42) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "--test="};

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
 *  Tests that cmdline::ParseNotCalled is thrown when calling
 *  is_flag_set() prior to calling parse()
 */

TEST(mygroup, IsFlagSetBeforeParse) {
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

TEST(mygroup, IsIntoptSetBeforeParse) {
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

TEST(mygroup, IsStroptSetBeforeParse) {
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

TEST(mygroup, IsPosargSetBeforeParse) {
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

TEST(mygroup, GetIntoptValueBeforeParse) {
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

TEST(mygroup, GetStroptValueBeforeParse) {
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

TEST(mygroup, GetPosargsBeforeParse) {
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

TEST(mygroup, SetProgramNameAfterParse) {
    int t_argc = 1;
    const char * t_argv[] = {"pridil"};
    cmdline::CmdLineOptions clopt;

    try {
        clopt.parse(t_argc, t_argv);
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

TEST(mygroup, SetVersionNumberAfterParse) {
    int t_argc = 1;
    const char * t_argv[] = {"pridil"};
    cmdline::CmdLineOptions clopt;

    try {
        clopt.parse(t_argc, t_argv);
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

TEST(mygroup, SetConfigFileOptionAfterParse) {
    int t_argc = 1;
    const char * t_argv[] = {"pridil"};
    cmdline::CmdLineOptions clopt;

    try {
        clopt.parse(t_argc, t_argv);
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

TEST(mygroup, SetIntOptAfterParse) {
    int t_argc = 1;
    const char * t_argv[] = {"pridil"};
    cmdline::CmdLineOptions clopt;

    try {
        clopt.parse(t_argc, t_argv);
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

TEST(mygroup, SetStrOptAfterParse) {
    int t_argc = 1;
    const char * t_argv[] = {"pridil"};
    cmdline::CmdLineOptions clopt;

    try {
        clopt.parse(t_argc, t_argv);
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

TEST(mygroup, SetFlagAfterParse) {
    int t_argc = 1;
    const char * t_argv[] = {"pridil"};
    cmdline::CmdLineOptions clopt;

    try {
        clopt.parse(t_argc, t_argv);
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


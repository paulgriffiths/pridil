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
    catch(cmdline::BadOptionValue) {

        /*  Test succeeds if we get here  */

    }
    catch(...) {
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
    catch(cmdline::BadOptionValue) {

        /*  Test succeeds if we get here  */

    }
    catch(...) {
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
    catch(cmdline::BadOptionValue) {

        /*  Test succeeds if we get here  */

    }
    catch(...) {
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
    catch(cmdline::BadOptionValue) {

        /*  Test succeeds if we get here  */

    }
    catch(...) {
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
    catch(cmdline::MissingOptionValue) {

        /*  Test succeeds if we get here  */

    }
    catch(...) {
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
    catch(cmdline::MissingOptionValue) {

        /*  Test succeeds if we get here  */

    }
    catch(...) {
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
    catch(cmdline::MissingOptionValue) {

        /*  Test succeeds if we get here  */

    }
    catch(...) {
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
    catch(cmdline::MissingOptionValue) {

        /*  Test succeeds if we get here  */

    }
    catch(...) {
        FAIL("Wrong exception thrown on missing intopt value");
    }
}


/*
 *  Tests that correct integer option is returned when using
 *  short format option with no '=' sign.
 */

TEST(IntOptGroup, IntOptValueTest) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "-t42", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_intopt("test", "-t", "--test", "test desc", false, 0);
    clopt.parse(t_argc, t_argv);

    try {
        int t_val = clopt.get_intopt_value("test");
        CHECK_EQUAL(t_val, 42);
    }
    catch(cmdline::OptionNotProvided) {
        FAIL("OptionNotProvided incorrectly thrown on good intopt");
    }
    catch(...) {
        FAIL("Unknown exception incorrectly thrown on good intopt");
    }
}


/*
 *  Tests that correct integer option is returned when using
 *  short format option with '=' sign.
 */

TEST(IntOptGroup, IntOptValueTest2) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "-t=42", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_intopt("test", "-t", "--test", "test desc", false, 0);
    clopt.parse(t_argc, t_argv);

    try {
        int t_val = clopt.get_intopt_value("test");
        CHECK_EQUAL(t_val, 42);
    }
    catch(cmdline::OptionNotProvided) {
        FAIL("OptionNotProvided incorrectly thrown on good intopt");
    }
    catch(...) {
        FAIL("Unknown exception incorrectly thrown on good intopt");
    }
}


/*
 *  Tests that correct integer option is returned when using
 *  long format option with no '=' sign.
 */

TEST(IntOptGroup, IntOptValueTest3) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "--test42", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_intopt("test", "-t", "--test", "test desc", false, 0);
    clopt.parse(t_argc, t_argv);

    try {
        int t_val = clopt.get_intopt_value("test");
        CHECK_EQUAL(t_val, 42);
    }
    catch(cmdline::OptionNotProvided) {
        FAIL("OptionNotProvided incorrectly thrown on good intopt");
    }
    catch(...) {
        FAIL("Unknown exception incorrectly thrown on good intopt");
    }
}


/*
 *  Tests that correct integer option is returned when using
 *  long format option with '=' sign.
 */

TEST(IntOptGroup, IntOptValueTest4) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "--test=42", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_intopt("test", "-t", "--test", "test desc", false, 0);
    clopt.parse(t_argc, t_argv);

    try {
        int t_val = clopt.get_intopt_value("test");
        CHECK_EQUAL(t_val, 42);
    }
    catch(cmdline::OptionNotProvided) {
        FAIL("OptionNotProvided incorrectly thrown on good intopt");
    }
    catch(...) {
        FAIL("Unknown exception incorrectly thrown on good intopt");
    }
}


/*
 *  Tests that integer option is reported as being set when it is provided.
 */

TEST(IntOptGroup, IntOptSetTest1) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "--test=42", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_intopt("test", "-t", "--test", "test desc", false, 0);
    clopt.parse(t_argc, t_argv);

    CHECK(clopt.is_intopt_set("test"));
}


/*
 *  Tests that integer option is reported as being not set when
 *  it is not provided, but another integer option is.
 */

TEST(IntOptGroup, IntOptSetTest2) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "--test=42", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_intopt("test", "-t", "--test", "test desc", false, 0);
    clopt.parse(t_argc, t_argv);

    CHECK(clopt.is_intopt_set("bogus_option") == false);
}


/*
 *  Tests that integer option is reported as being not set when
 *  it is not provided, and no other integer options are provided.
 */

TEST(IntOptGroup, IntOptSetTest3) {
    int t_argc = 1;
    const char * t_argv[] = {"pridil", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.parse(t_argc, t_argv);

    CHECK(clopt.is_intopt_set("bogus_option") == false);
}


/*
 *  Tests that a default integer option is correctly set when that
 *  integer option is not provided.
 */

TEST(IntOptGroup, IntOptDefaultTest) {
    int t_argc = 1;
    const char * t_argv[] = {"pridil", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_intopt("test", "-t", "--test", "test desc", true, 42);
    clopt.parse(t_argc, t_argv);

    try {
        int t_val = clopt.get_intopt_value("test");
        CHECK_EQUAL(t_val, 42);
    }
    catch(cmdline::OptionNotProvided) {
        FAIL("OptionNotProvided incorrectly thrown on default intopt");
    }
    catch(...) {
        FAIL("Unknown exception incorrectly thrown on default intopt");
    }
}


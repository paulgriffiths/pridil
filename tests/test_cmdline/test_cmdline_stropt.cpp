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

#include <string>

#include "../../cmdline.h"


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
    catch(cmdline::MissingOptionValue) {

        /*  Test succeeds if we get here  */

    }
    catch(...) {
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
    catch(cmdline::MissingOptionValue) {

        /*  Test succeeds if we get here  */

    }
    catch(...) {
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
    catch(cmdline::MissingOptionValue) {

        /*  Test succeeds if we get here  */

    }
    catch(...) {
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
    catch(cmdline::MissingOptionValue) {

        /*  Test succeeds if we get here  */

    }
    catch(...) {
        FAIL("Wrong exception thrown on missing stropt value");
    }
}


/*
 *  Tests that correct string option is returned when using
 *  short format option with no '=' sign.
 */

TEST(StrOptGroup, StrOptValueTest) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "-tfoobar", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_stropt("test", "-t", "--test", "test desc", false, "");
    clopt.parse(t_argc, t_argv);

    try {
        std::string t_val = clopt.get_stropt_value("test");
        CHECK_EQUAL(t_val, std::string("foobar"));
    }
    catch(cmdline::OptionNotProvided) {
        FAIL("OptionNotProvided incorrectly thrown on good stropt");
    }
    catch(...) {
        FAIL("Unknown exception incorrectly thrown on good stropt");
    }
}


/*
 *  Tests that correct string option is returned when using
 *  short format option with '=' sign.
 */

TEST(StrOptGroup, StrOptValueTest2) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "-t=foobar", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_stropt("test", "-t", "--test", "test desc", false, "");
    clopt.parse(t_argc, t_argv);

    try {
        std::string t_val = clopt.get_stropt_value("test");
        CHECK_EQUAL(t_val, std::string("foobar"));
    }
    catch(cmdline::OptionNotProvided) {
        FAIL("OptionNotProvided incorrectly thrown on good stropt");
    }
    catch(...) {
        FAIL("Unknown exception incorrectly thrown on good stropt");
    }
}


/*
 *  Tests that correct string option is returned when using
 *  long format option with no '=' sign.
 */

TEST(StrOptGroup, StrOptValueTest3) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "--testfoobar", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_stropt("test", "-t", "--test", "test desc", false, "");
    clopt.parse(t_argc, t_argv);

    try {
        std::string t_val = clopt.get_stropt_value("test");
        CHECK_EQUAL(t_val, std::string("foobar"));
    }
    catch(cmdline::OptionNotProvided) {
        FAIL("OptionNotProvided incorrectly thrown on good stropt");
    }
    catch(...) {
        FAIL("Unknown exception incorrectly thrown on good stropt");
    }
}


/*
 *  Tests that correct string option is returned when using
 *  long format option with '=' sign.
 */

TEST(StrOptGroup, StrOptValueTest4) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "--test=foobar", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_stropt("test", "-t", "--test", "test desc", false, "");
    clopt.parse(t_argc, t_argv);

    try {
        std::string t_val = clopt.get_stropt_value("test");
        CHECK_EQUAL(t_val, std::string("foobar"));
    }
    catch(cmdline::OptionNotProvided) {
        FAIL("OptionNotProvided incorrectly thrown on good stropt");
    }
    catch(...) {
        FAIL("Unknown exception incorrectly thrown on good stropt");
    }
}


/*
 *  Tests that string option is reported as being set when it is provided.
 */

TEST(StrOptGroup, StrOptSetTest1) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "--test=foobar", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_stropt("test", "-t", "--test", "test desc", false, "");
    clopt.parse(t_argc, t_argv);

    CHECK(clopt.is_stropt_set("test"));
}


/*
 *  Tests that string option is reported as being not set when
 *  it is not provided, but another string option is.
 */

TEST(StrOptGroup, StrOptSetTest2) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "--test=foobar", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_stropt("test", "-t", "--test", "test desc", false, "");
    clopt.parse(t_argc, t_argv);

    CHECK(clopt.is_stropt_set("bogus_option") == false);
}


/*
 *  Tests that string option is reported as being not set when
 *  it is not provided, and no other string options are provided.
 */

TEST(StrOptGroup, StrOptSetTest3) {
    int t_argc = 1;
    const char * t_argv[] = {"pridil", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.parse(t_argc, t_argv);

    CHECK(clopt.is_stropt_set("bogus_option") == false);
}


/*
 *  Tests that a default string option is correctly set when that
 *  string option is not provided.
 */

TEST(StrOptGroup, StrOptDefaultTest) {
    int t_argc = 1;
    const char * t_argv[] = {"pridil", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_stropt("test", "-t", "--test", "test desc", true, "dongle");
    clopt.parse(t_argc, t_argv);

    try {
        std::string t_val = clopt.get_stropt_value("test");
        CHECK_EQUAL(t_val, std::string("dongle"));
    }
    catch(cmdline::OptionNotProvided) {
        FAIL("OptionNotProvided incorrectly thrown on default stropt");
    }
    catch(...) {
        FAIL("Unknown exception incorrectly thrown on default stropt");
    }
}


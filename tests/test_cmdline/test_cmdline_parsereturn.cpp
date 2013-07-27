/*
 *
 *  test_cmdline_parsereturn.cpp
 *  ============================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  CmdLineOptions class unit tests for return value of parse().
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>

#include <iostream>
#include <sstream>
#include <streambuf>

#include "../../cmdline.h"

TEST_GROUP(ParseReturnGroup) {
};


/*
 *  Tests that parse() returns true under normal circumstances.
 */

TEST(ParseReturnGroup, ReturnTrueTest) {
    int t_argc = 1;
    const char * t_argv[] = {"pridil", NULL};

    cmdline::CmdLineOptions clopt;
    bool b_val = clopt.parse(t_argc, t_argv);
    CHECK_EQUAL(b_val, true);
}


/*
 *  Tests that parse() returns false when invoked with -h flag.
 *
 *  Note: this test temporarily redirects std::cout to avoid actually
 *  printing the help message to standard out.
 */

TEST(ParseReturnGroup, ReturnFalseHelpTest) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "-h", NULL};

    cmdline::CmdLineOptions clopt;

    std::ostringstream divert;
    std::streambuf * old_cout = std::cout.rdbuf(divert.rdbuf());

    bool b_val = clopt.parse(t_argc, t_argv);

    std::cout.rdbuf(old_cout);

    CHECK_EQUAL(b_val, false);
}


/*
 *  Tests that parse() returns false when invoked with -v flag.
 *
 *  Note: this test temporarily redirects std::cout to avoid actually
 *  printing the version message to standard out.
 */

TEST(ParseReturnGroup, ReturnFalseVersionTest) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "-v", NULL};

    cmdline::CmdLineOptions clopt;

    std::ostringstream divert;
    std::streambuf * old_cout = std::cout.rdbuf(divert.rdbuf());

    bool b_val = clopt.parse(t_argc, t_argv);

    std::cout.rdbuf(old_cout);

    CHECK_EQUAL(b_val, false);
}


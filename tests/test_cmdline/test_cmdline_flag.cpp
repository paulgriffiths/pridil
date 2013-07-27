/*
 *
 *  test_cmdline_flag.cpp
 *  =====================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  CmdLineOptions class unit tests for flags.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../../cmdline.h"

TEST_GROUP(FlagGroup) {
};


/*
 *  Tests that flag is reported as being set when it is provided in
 *  short flag form.
 */

TEST(FlagGroup, FlagSetTest1) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "-t", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_flag("test", "-t", "--test", "test desc", false);
    clopt.parse(t_argc, t_argv);

    CHECK(clopt.is_flag_set("test"));
}


/*
 *  Tests that flag is reported as being set when it is provided in
 *  long flag form.
 */

TEST(FlagGroup, FlagSetTest1a) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "--test", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_flag("test", "-t", "--test", "test desc", false);
    clopt.parse(t_argc, t_argv);

    CHECK(clopt.is_flag_set("test"));
}


/*
 *  Tests that flag is reported as being not set when
 *  it is not provided, but another flag is.
 */

TEST(FlagGroup, FlagSetTest2) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "-t", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_flag("test", "-t", "--test", "test desc", false);
    clopt.parse(t_argc, t_argv);

    CHECK(clopt.is_flag_set("bogus_option") == false);
}


/*
 *  Tests that flag is reported as being not set when
 *  it is not provided, and no other flags are provided.
 */

TEST(FlagGroup, FlagSetTest3) {
    int t_argc = 1;
    const char * t_argv[] = {"pridil", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.parse(t_argc, t_argv);

    CHECK(clopt.is_flag_set("bogus_option") == false);
}


/*
 *  Tests that a default flag is correctly set when that
 *  flag is not provided.
 */

TEST(FlagGroup, FlagDefaultTest) {
    int t_argc = 1;
    const char * t_argv[] = {"pridil", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_flag("test", "-t", "--test", "test desc", true);
    clopt.parse(t_argc, t_argv);

    CHECK(clopt.is_flag_set("test"));
}


/*
 *
 *  test_cmdline_posarg.cpp
 *  =======================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  CmdLineOptions class unit tests for positional arguments.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>

#include <string>
#include <list>

#include "../../cmdline.h"


TEST_GROUP(PosargGroup) {
};


/*
 *  Tests that posarg is reported as being set when it is provided
 *  by itself.
 */

TEST(PosargGroup, PosargSetTest1) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil", "posarg1", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.parse(t_argc, t_argv);

    CHECK(clopt.is_posarg_set("posarg1"));
}


/*
 *  Tests that two posargs are both reported as being set when
 *  they are both provided.
 */

TEST(PosargGroup, PosargSetTest2) {
    int t_argc = 3;
    const char * t_argv[] = {"pridil", "posarg1", "posarg2", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.parse(t_argc, t_argv);

    CHECK(clopt.is_posarg_set("posarg1"));
    CHECK(clopt.is_posarg_set("posarg2"));
}


/*
 *  Tests that a posarg not provided is reported as unset when two
 *  other posargs are provided.
 */

TEST(PosargGroup, PosargSetTest3) {
    int t_argc = 3;
    const char * t_argv[] = {"pridil", "posarg1", "posarg2", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.parse(t_argc, t_argv);

    CHECK(clopt.is_posarg_set("bogus_arg") == false);
}


/*
 *  Tests that the list returned by get_pos_args() contains all
 *  the posargs provided, in the order provided.
 */

TEST(PosargGroup, GetPosargsTest) {
    int t_argc = 3;
    const char * t_argv[] = {"pridil", "posarg1", "posarg2", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.parse(t_argc, t_argv);

    std::list<std::string> check_list;
    check_list.push_back("posarg1");
    check_list.push_back("posarg2");

    CHECK(clopt.get_pos_args() == check_list);
}


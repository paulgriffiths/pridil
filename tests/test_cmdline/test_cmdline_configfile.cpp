/*
 *
 *  test_cmdline_configfile.cpp
 *  ===========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  CmdLineOptions class unit tests for configuration files.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../../cmdline.h"

TEST_GROUP(CFileGroup) {
};



/*
 *  Tests that ConfigFileOpenFailed is correctly thrown when
 *  passing a non-existent config filename.
 */

TEST(CFileGroup, ConfigFileBadNameTest) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil",
        "-c=tests/test_cmdline/cmdline-config-bogus", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_stropt("cfile", "-c", "--cfile", "config file", "");
    clopt.set_config_file_option("cfile");
    try {
        clopt.parse(t_argc, t_argv);
        FAIL("ConfigFileOpenFailed not thrown when expected.");
    }
    catch(cmdline::ConfigFileOpenFailed) {

        /*  Test succeeds if we get here  */

    }
    catch(...) {
        FAIL("Unexpected exception thrown by parse()");
    }
}


/*
 *  Tests that correct options and flags are set from a config file.
 *
 *  A test configuration file should exist, named cmdline-config-sample,
 *  with the following content:
 *
 *      option1=42
 *      option2=orderly
 *      flag1
 *
 *  This unit test assumes that the test configuration file will reside
 *  in a directory called 'tests/test_cmdline' contained within the
 *  directory that the unit test executable is called from.
 */

TEST(CFileGroup, ConfigFileValueTest) {
    int t_argc = 2;
    const char * t_argv[] = {"pridil",
        "-c=tests/test_cmdline/cmdline-config-sample", NULL};

    cmdline::CmdLineOptions clopt;
    clopt.set_stropt("cfile", "-c", "--cfile", "config file", "");
    clopt.set_config_file_option("cfile");
    clopt.parse(t_argc, t_argv);

    int t_val = clopt.get_intopt_value("option1");
    CHECK_EQUAL(t_val, 42);

    std::string t_str = clopt.get_stropt_value("option2");
    CHECK_EQUAL(t_str, std::string("orderly"));

    CHECK(clopt.is_flag_set("flag1"));
}


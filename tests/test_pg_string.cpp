/*
 *
 *  test_pg_string.cpp
 *  ==================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for PG string helper functions.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include <string>
#include "../pg_string_helpers.h"

using pg_string::trim_left;
using pg_string::trim_right;
using pg_string::trim;
using pg_string::lowercase;
using pg_string::uppercase;
using pg_string::get_key_value;
using pg_string::stdstring_to_int;


TEST_GROUP(PGStringGroup) {
};


/*
 *  Tests trim_left() function
 */

TEST(PGStringGroup, TrimLeftTest) {
    std::string check_string = " mystring";
    CHECK_EQUAL(trim_left(check_string), std::string("mystring"));

    check_string = "   mystring";
    CHECK_EQUAL(trim_left(check_string), std::string("mystring"));

    check_string = "   mystring  ";
    CHECK_EQUAL(trim_left(check_string), std::string("mystring  "));

    check_string = "mystring";
    CHECK_EQUAL(trim_left(check_string), std::string("mystring"));

    check_string = "mystring space";
    CHECK_EQUAL(trim_left(check_string), std::string("mystring space"));
}


/*
 *  Tests trim_right() function
 */

TEST(PGStringGroup, TrimRightTest) {
    std::string check_string = "mystring ";
    CHECK_EQUAL(trim_right(check_string), std::string("mystring"));

    check_string = "mystring   ";
    CHECK_EQUAL(trim_right(check_string), std::string("mystring"));

    check_string = "  mystring   ";
    CHECK_EQUAL(trim_right(check_string), std::string("  mystring"));

    check_string = "mystring";
    CHECK_EQUAL(trim_right(check_string), std::string("mystring"));

    check_string = "mystring space";
    CHECK_EQUAL(trim_right(check_string), std::string("mystring space"));
}


/*
 *  Tests trim() function
 */

TEST(PGStringGroup, TrimTest) {
    std::string check_string = "mystring ";
    CHECK_EQUAL(trim(check_string), std::string("mystring"));

    check_string = "mystring   ";
    CHECK_EQUAL(trim(check_string), std::string("mystring"));

    check_string = "  mystring   ";
    CHECK_EQUAL(trim(check_string), std::string("mystring"));

    check_string = "mystring";
    CHECK_EQUAL(trim(check_string), std::string("mystring"));

    check_string = "mystring space";
    CHECK_EQUAL(trim(check_string), std::string("mystring space"));

    check_string = "   mystring space    ";
    CHECK_EQUAL(trim(check_string), std::string("mystring space"));
}


/*
 *  Tests lowercase() function
 */

TEST(PGStringGroup, LowerCaseTest) {
    std::string check_string = "MYSTRING";
    CHECK_EQUAL(lowercase(check_string), std::string("mystring"));

    check_string = "MyStRiNg";
    CHECK_EQUAL(lowercase(check_string), std::string("mystring"));

    check_string = "mYsTrInG";
    CHECK_EQUAL(lowercase(check_string), std::string("mystring"));

    check_string = "  mySTRing SpacE  ";
    CHECK_EQUAL(lowercase(check_string), std::string("  mystring space  "));
}


/*
 *  Tests uppercase() function
 */

TEST(PGStringGroup, UpperCaseTest) {
    std::string check_string = "mystring";
    CHECK_EQUAL(uppercase(check_string), std::string("MYSTRING"));

    check_string = "MyStRiNg";
    CHECK_EQUAL(uppercase(check_string), std::string("MYSTRING"));

    check_string = "mYsTrInG";
    CHECK_EQUAL(uppercase(check_string), std::string("MYSTRING"));

    check_string = "  mySTRing SpacE  ";
    CHECK_EQUAL(uppercase(check_string), std::string("  MYSTRING SPACE  "));
}


/*
 *  Tests get_key_value() function
 */

TEST(PGStringGroup, GetKeyValueTest) {
    std::string check_string = "k=v";
    std::pair<std::string, std::string> check_pair;

    check_pair = get_key_value(check_string);
    CHECK(check_pair.first == "k");
    CHECK(check_pair.second == "v");

    check_string="p1/p2";
    check_pair = get_key_value(check_string, '/');
    CHECK(check_pair.first == "p1");
    CHECK(check_pair.second == "p2");

    check_string="boat";
    check_pair = get_key_value(check_string);
    CHECK(check_pair.first == "boat");
    CHECK(check_pair.second == "");

    check_string="rifle=";
    check_pair = get_key_value(check_string);
    CHECK(check_pair.first == "rifle");
    CHECK(check_pair.second == "");

    check_string="war = peace";
    check_pair = get_key_value(check_string);
    CHECK(check_pair.first == "war");
    CHECK(check_pair.second == "peace");

    check_string="  freedom   = slavery     ";
    check_pair = get_key_value(check_string);
    CHECK(check_pair.first == "freedom");
    CHECK(check_pair.second == "slavery");
}


/*
 *  Tests stdstring_to_int() function
 */

TEST(PGStringGroup, StrToIntTest) {
    std::string check_string = "123";

    int t_val = stdstring_to_int(check_string);
    CHECK_EQUAL(t_val, 123);

    check_string = "0x123";
    t_val = stdstring_to_int(check_string, 16);
    CHECK_EQUAL(t_val, 291);

    check_string = "123";
    t_val = stdstring_to_int(check_string, 16);
    CHECK_EQUAL(t_val, 291);

    check_string = "123";
    t_val = stdstring_to_int(check_string, 8);
    CHECK_EQUAL(t_val, 83);

    check_string = "0123";
    t_val = stdstring_to_int(check_string, 8);
    CHECK_EQUAL(t_val, 83);

    check_string = "1101101011101";
    t_val = stdstring_to_int(check_string, 2);
    CHECK_EQUAL(t_val, 7005);

    check_string = "123BogusCharacters";
    try {
        t_val = stdstring_to_int(check_string);
        FAIL("BadValue not thrown by stdstring_to_int()");
    }
    catch(pg_string::BadValue) {

        /*  Test succeeds if we get here  */

    }
    catch(...) {
        FAIL("Unknown exception thrown by stdstring_to_int()");
    }

    check_string = "BogusCharacters";
    try {
        t_val = stdstring_to_int(check_string);
        FAIL("BadValue not thrown by stdstring_to_int()");
    }
    catch(pg_string::BadValue) {

        /*  Test succeeds if we get here  */

    }
    catch(...) {
        FAIL("Unknown exception thrown by stdstring_to_int()");
    }
}

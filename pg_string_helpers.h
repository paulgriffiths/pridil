/*
 *  pg_string_helpers.h
 *  ===================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  A general purpose string handling library.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_STRING_HELPERS_H
#define PG_STRING_HELPERS_H

#include <string>

namespace pg_string {

    //  Using declarations

    using std::string;
    using std::pair;


    //  BadValue() exception class thrown by stdstring_to_int()

    class BadValue {};


    //  Function declarations

    string& trim(string& in_str);
    string& trim_right(string& in_str);
    string& trim_left(string& in_str);
    string& lowercase(string& in_str);
    string& uppercase(string& in_str);
    pair<string, string> get_key_value(const string& kvpair,
                                       const char delim = '=');
    int stdstring_to_int(const string& in_str, const int base = 10);
}

#endif      // PG_STRING_HELPERS_H

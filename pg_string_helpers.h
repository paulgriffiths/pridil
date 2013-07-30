/*
 *  pg_string_helpers.h
 *  ===================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  A general purpose std::string handling library.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_STRING_HELPERS_H
#define PG_STRING_HELPERS_H

#include <string>

namespace pg_string {

    //  BadValue() exception class thrown by stdstring_to_int()

    class BadValue {};

    //  Function declarations

    std::string& trim(std::string& in_str);
    std::string& trim_right(std::string& in_str);
    std::string& trim_left(std::string& in_str);
    std::string& lowercase(std::string& in_str);
    std::string& uppercase(std::string& in_str);
    std::pair<std::string, std::string> get_key_value(const std::string& kvpair,
                                                      const char delim = '=');
    int stdstring_to_int(const std::string& in_str, const int base = 10);
}

#endif      // PG_STRING_HELPERS_H

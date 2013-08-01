/*
 *  pg_string_helpers.cpp
 *  =====================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  A general purpose string handling library.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 *
 *  Implementation.
 */


#include <algorithm>
#include <string>
#include <utility>
#include <cctype>

#include "pg_string_helpers.h"

using std::string;
using std::pair;


/*
 *  Trims leading and trailing whitespace from a string.
 *
 *  Arguments:
 *    in_str -- the string to trim, this argument is modified.
 *
 *  Returns:
 *    A reference to the modified string.
 */

string& pg_string::trim(string& in_str) {
    return trim_left(trim_right(in_str));
}


/*
 *  Trims trailing whitespace from a string.
 *
 *  Arguments:
 *    in_str -- the string to trim, this argument is modified.
 *
 *  Returns:
 *    A reference to the modified string.
 */

string& pg_string::trim_right(string& in_str) {
    size_t len = in_str.length();
    int n = len - 1;

    while ( n >= 0 && isspace(in_str[n]) ) {
        --n;
    }

    in_str = in_str.substr(0, n+1);
    return in_str;
}


/*
 *  Trims leading whitespace from a string.
 *
 *  Arguments:
 *    in_str -- the string to trim, this argument is modified.
 *
 *  Returns:
 *    A reference to the modified string.
 */

string& pg_string::trim_left(string& in_str) {
    size_t len = in_str.length();
    size_t n = 0;

    while ( n < len && isspace(in_str[n]) ) {
        ++n;
    }

    in_str = in_str.substr(n);
    return in_str;
}


/*
 *  Converts a string to lower case.
 *
 *  Arguments:
 *    in_str -- the string to convert, this argument is modified.
 *
 *  Returns:
 *    A reference to the modified string.
 */

string& pg_string::lowercase(string& in_str) {
    size_t len = in_str.length();
    size_t n = 0;

    while ( n < len ) {
        in_str[n] = tolower(in_str[n]);
        ++n;
    }

    return in_str;
}


/*
 *  Converts a string to upper case.
 *
 *  Arguments:
 *    in_str -- the string to convert, this argument is modified.
 *
 *  Returns:
 *    A reference to the modified string.
 */

string& pg_string::uppercase(string& in_str) {
    size_t len = in_str.length();
    size_t n = 0;

    while ( n < len ) {
        in_str[n] = toupper(in_str[n]);
        ++n;
    }

    return in_str;
}


/*
 *  Parses a delimited key/value pair into its components.
 *
 *  Arguments:
 *    kvpair -- the string to parse.
 *    delim -- delimiter character (default is '=')
 *
 *  Returns:
 *    A std::pair<std::string, std::string> containing the parsed
 *    key and its value, in that order. Note that the value may
 *    be an empty string, if the delimiter is the final character.
 */

pair<string, string> pg_string::get_key_value(const string& kvpair,
                                              const char delim) {
    string key, value;
    string::const_iterator delim_itr = find(kvpair.begin(), kvpair.end(),
                                            delim);

    key = string(kvpair.begin(), delim_itr);
    if ( delim_itr != kvpair.end() ) {
        value = string(++delim_itr, kvpair.end());
    }

    trim(key);
    trim(value);
    return pair<string, string> (key, value);
}


/*
 *  Converts a std::string to an int.
 *
 *  This argument is a wrapper around the standard C strtol() function.
 *
 *  Arguments:
 *    in_str -- the string to convert. Trailing and leading whitespace
 *      is trimmed prior to conversion, the argument is not modified.
 *
 *  Returns:
 *    An int representing the integer value of the string.
 *
 *  Exceptions thrown:
 *    BadValue() if the string contains anything other than digits.
 */

int pg_string::stdstring_to_int(const string& in_str, const int base) {
    string trimmed_string = in_str;
    trim(trimmed_string);

    const char * csval = trimmed_string.c_str();
    char * endptr = 0;
    const int value = strtol(csval, &endptr, base);

    if ( *endptr != '\0' ) {
        throw BadValue();
    }

    return static_cast<int> (value);
}

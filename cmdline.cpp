/*
 *  cmdline.cpp
 *  ===========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  A general purpose command line argument and configuration file
 *  parsing class.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 *
 *  Implementation.
 */


#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <cassert>

#include "cmdline.h"
#include "pg_string_helpers.h"

using cmdline::CmdLineOptions;
using std::string;
using std::list;
using std::map;
using std::cout;
using std::cerr;
using std::endl;
using std::ostringstream;
using std::ifstream;
using std::getline;
using std::find;
using std::pair;


/*
 *  Constructor
 *
 *  Initializes members, and defines two always-present flags.
 */

CmdLineOptions::CmdLineOptions()
        : m_program_name(), m_version_number(), m_executable_name(),
          m_config_file_option(), m_intopt_defs(), m_stropt_defs(),
          m_flag_defs(), m_intopts(), m_stropts(), m_flags(),
          m_posargs(), m_parse_called(false) {
    m_flag_defs.push_back(FlagDef("help", "-h", "--help",
                                  "show help and usage information",
                                  false));
    m_flag_defs.push_back(FlagDef("version", "-v", "--version",
                                  "show version information",
                                  false));
}


/*
 *  Optionally sets the program name, for use in the show_help() method.
 */

void CmdLineOptions::set_program_name(const string& program_name) {
    assert(!m_parse_called);
    m_program_name = program_name;
}


/*
 *  Optionally sets the program version number, for use in the show_help()
 *  and show_version() methods.
 */

void CmdLineOptions::set_version_number(const string& version_number) {
    assert(!m_parse_called);
    m_version_number = version_number;
}


/*
 *  Optionally identifies the string option which will be used to
 *  provide the name of a configuration file.
 *
 *  When calling this method, the caller should also call the
 *  set_stropt() method to actually provide the option definition
 *  for which this identification is provided.
 *
 *  Even if a configuration file option is defined, and this method
 *  is called, the configuration file will not be read if the
 *  specified option is not provided on the command line.
 */

void CmdLineOptions::set_config_file_option(const string& option) {
    assert(!m_parse_called);
    m_config_file_option = option;
}


/*
 *  Sets a definition for an integer option which may be provided.
 *
 *  Optionally sets the default value for that option.
 *
 *  Arguments:
 *    name -- the name of the option, by which it will be referred to.
 *            This is the value that will be used as the key by the
 *            std::map container to hold the definitions, and the key
 *            which must be provided to obtain the value of that option
 *            or to check whether it has been set.
 *    short_option -- the short option string by which the option will
 *                    be specified on the command line, e.g. '-v'.
 *    long_option -- the long option string by which the option will be
 *                   specified on the command line, e.g. '--version'.
 *    description -- a description which will be displayed alongside
 *                   the option when the help message is shown.
 *    has_default -- true if the option has a default value
 *    default_value -- the default value to be used, if has_default is
 *                     set to true.
 */

void CmdLineOptions::set_intopt(const string& name,
                                const string& short_option,
                                const string& long_option,
                                const string& description,
                                const bool has_default,
                                const int default_value) {
    m_intopt_defs.push_back(IntOptDef(name, short_option, long_option,
                                      description, has_default,
                                      default_value));
    assert(!m_parse_called);
    if ( has_default ) {
        m_intopts[name] = default_value;
    }
}


/*
 *  Sets a definition for a string option which may be provided.
 *
 *  Optionally sets a default value for that option.
 *
 *  Arguments:
 *    name -- the name of the option, by which it will be referred to.
 *            This is the value that will be used as the key by the
 *            std::map container to hold the definitions, and the key
 *            which must be provided to obtain the value of that option
 *            or to check whether it has been set.
 *    short_option -- the short option string by which the option will
 *                    be specified on the command line, e.g. '-v'.
 *    long_option -- the long option string by which the option will be
 *                   specified on the command line, e.g. '--version'.
 *    description -- a description which will be displayed alongside
 *                   the option when the help message is shown.
 *    has_default -- true if the option has a default value
 *    default_value -- the default value to be used, if has_default is
 *                     set to true.
 */

void CmdLineOptions::set_stropt(const string& name,
                                const string& short_option,
                                const string& long_option,
                                const string& description,
                                const bool has_default,
                                const string& default_value) {
    m_stropt_defs.push_back(StrOptDef(name, short_option, long_option,
                                      description, has_default,
                                      default_value));
    assert(!m_parse_called);
    if ( has_default ) {
        m_stropts[name] = default_value;
    }
}


/*
 *  Sets a definition for a flag which may be provided.
 *
 *  Optionally sets that flag by default.
 *
 *  Arguments:
 *    name -- the name of the flag, by which it will be referred to.
 *            This is the value that will be used as the key by the
 *            std::map container to hold the definitions, and the key
 *            which must be provided to check whether it has been set.
 *    short_option -- the short option string by which the flag will
 *                    be specified on the command line, e.g. '-v'.
 *    long_option -- the long option string by which the flag will be
 *                   specified on the command line, e.g. '--version'.
 *    description -- a description which will be displayed alongside
 *                   the flag when the help message is shown.
 *    deault_on -- true if the flag is to be set by default.
 */

void CmdLineOptions::set_flag(const string& name,
                              const string& short_flag,
                              const string& long_flag,
                              const string& description,
                              const bool default_on) {
    assert(!m_parse_called);
    m_flag_defs.push_back(FlagDef(name, short_flag, long_flag, description,
                                  default_on));
    if ( default_on ) {
        m_flags[name] = true;
    }
}


/*
 *  Parses command line arguments for flags, options and positional
 *  arguments (positional arguments are those left over once flags
 *  and options have been identified.) 
 *
 *  Also displays the help message or a version message if the appropriate
 *  flags are set. Further, it reads in options from a configuration file
 *  if one has been specified.
 *
 *  Arguments:
 *    argc, argv -- regular command line arguments passed to main()
 *
 *  Returns:
 *    false if the help message or version message has been displayed
 *    (normally the caller would terminate the program after displaying
 *    these messages), true otherwise.
 *
 *  Exceptions thrown:
 *    BadExecutableName() if argc < 1 (rare)
 *
 */

bool CmdLineOptions::parse(const int argc, char const* const* argv) {

    //  Store program name

    if ( argc < 1 ) {
       throw BadExecutableName();
    } else {
       m_executable_name = argv[0];
    }

    //  Parse flags, options and positional arguments

    int n = 0;
    while ( ++n < argc ) {
        if ( !check_arg_for_flag(argv[n]) ) {
            if ( !check_arg_for_intopt(argv[n]) ) {
                if ( !check_arg_for_stropt(argv[n]) ) {
                    m_posargs.push_back(argv[n]);
                }
            }
        }
    }

    m_parse_called = true;


    //  Show help or version information if set

    if ( is_flag_set("help") ) {
        show_help();
        return false;
    }
    if ( is_flag_set("version") ) {
        show_version();
        return false;
    }

    //  Process config file, if one exists

    if ( m_config_file_option != "" && is_stropt_set(m_config_file_option) ) {
        process_config_file();
    }

    return true;
}


/*
 *  Checks whether a specified flag has been set.
 */

bool CmdLineOptions::is_flag_set(const string& name) const {
    assert(m_parse_called);
    bool is_set = true;
    if ( m_flags.find(name) == m_flags.end() ) {
        is_set = false;
    }
    return is_set;
}


/*
 *  Checks whether a specified integer option has been set.
 */

bool CmdLineOptions::is_intopt_set(const std::string& option) const {
    assert(m_parse_called);
    bool is_set = true;
    if ( m_intopts.find(option) == m_intopts.end() ) {
        is_set = false;
    }
    return is_set;
}


/*
 *  Checks whether a specified string option has been set.
 */

bool CmdLineOptions::is_stropt_set(const std::string& option) const {
    assert(m_parse_called);
    bool is_set = true;
    if ( m_stropts.find(option) == m_stropts.end() ) {
        is_set = false;
    }
    return is_set;
}


/*
 *  Checks whether a specified positional argument has been provided.
 */

bool CmdLineOptions::is_posarg_set(const std::string& option) const {
    assert(m_parse_called);
    bool is_set = true;
    if ( find(m_posargs.begin(), m_posargs.end(), option) == m_posargs.end() ) {
        is_set = false;
    }
    return is_set;
}


/*
 *  Retrieves the value of a specified integer option.
 *
 *  Exceptions thrown:
 *    OptionNotProvided() if the option was not provided.
 */

int CmdLineOptions::get_intopt_value(const string& name) const {
    assert(m_parse_called);
    IntOptMap::const_iterator opt = m_intopts.find(name);
    if ( opt == m_intopts.end() ) {
        throw OptionNotProvided(name);
    }
    return (*opt).second;
}


/*
 *  Retrieves the value of a specified string option.
 *
 *  Exceptions thrown:
 *    OptionNotProvided() if the option was not provided.
 */

string CmdLineOptions::get_stropt_value(const string& name) const {
    assert(m_parse_called);
    StrOptMap::const_iterator opt = m_stropts.find(name);
    if ( opt == m_stropts.end() ) {
        throw OptionNotProvided(name);
    }
    return (*opt).second;
}


/*
 *  Returns a list of provided positional arguments.
 *
 *  Returns:
 *    A const std::list<std::string> containing the positional arguments.
 *    The return value is const to avoid returning a copy, the caller
 *    can assign (and therefore copy) it to a non-const list if she
 *    wants to.
 */

const list<string>& CmdLineOptions::get_pos_args() const {
    assert(m_parse_called);
    return m_posargs;
}


/*
 *   Checks whether a command line argument represents a pre-defined
 *   flag, and if so, updates the list of provided flags.
 *
 *   Arguments:
 *     arg -- the command line argument to check. The string argument
 *            is checked in its entirety again pre-defined flags. Either
 *            a short-form flag (e.g. '-h') or a long-form flag
 *            (e.g. '--help') will cause a match.
 *
 *   Returns:
 *     true is a pre-defined flag is found, false if not.
 */

bool CmdLineOptions::check_arg_for_flag(const string& arg) {
    bool found = false;
    for ( FlagDefList::const_iterator i = m_flag_defs.begin();
          found == false && i != m_flag_defs.end(); ++i ) {
        if ( arg == (*i).m_short_flag || arg == (*i).m_long_flag ) {
            m_flags[(*i).m_name] = true;
            found = true;
        }
    }
    return found;
}


/*
 *   Checks whether a command line argument represents a pre-defined
 *   integer option and, if so, updates the list of provided integer
 *   options.
 *
 *   If an option is found, the value is passed to parse_intopt()
 *   to be converted to an integer, which may throw a BadOptionValue()
 *   or a MissingOptionValue() exception if the value does not consist
 *   entirely of digits or is an empty string, respectively.
 *
 *   Arguments:
 *     arg -- the command line argument to check. An argument which
 *            successfully matches will be of the form:
 *
 *                "OPT=nnnn...." or "OPTnnnn...."
 *
 *            where 'OPT' is a pre-defined long- or short-option and
 *            'nnnn' is a sequence of one or more digits.
 *
 *   Returns:
 *     true is a pre-defined option is found, false if not.
 *
 *   Exceptions thrown:
 *     BadOptionValue() -- may be indirectly thrown by parse_int_opt()
 *     MissingOptionValue() -- may be indirectly thrown by parse_int_opt()
 */

bool CmdLineOptions::check_arg_for_intopt(const string& arg) {
    bool found = false;
    size_t short_len, long_len;
    for ( IntOptDefList::const_iterator i = m_intopt_defs.begin();
          found == false && i != m_intopt_defs.end(); ++i ) {
        short_len = (*i).m_short_opt.length();
        long_len = (*i).m_long_opt.length();

        if ( arg.substr(0, short_len) == (*i).m_short_opt ) {
            m_intopts[(*i).m_name] = parse_intopt(arg, (*i).m_short_opt);
            found = true;
        } else if ( arg.substr(0, long_len) == (*i).m_long_opt ) {
            m_intopts[(*i).m_name] = parse_intopt(arg, (*i).m_long_opt);
            found = true;
        }
    }
    return found;
}


/*
 *   Checks whether a command line argument represents a pre-defined
 *   string option and, if so, updates the list of provided string
 *   options.
 *
 *   If an option is found, the value is passed to parse_stropt(),
 *   which may throw a BadOptionValue() exception if the value is an
 *   empty string.
 *
 *   Arguments:
 *     arg -- the command line argument to check. An argument which
 *            successfully matches will be of the form:
 *
 *                "OPT=ssss...." or "OPTssss...."
 *
 *            where 'OPT' is a pre-defined long- or short-option and
 *            'ssss' is a sequence of one or more characters.
 *
 *   Returns:
 *     true is a pre-defined option is found, false if not.
 */

bool CmdLineOptions::check_arg_for_stropt(const string& arg) {
    bool found = false;
    size_t short_len, long_len;
    for ( StrOptDefList::const_iterator i = m_stropt_defs.begin();
          found == false && i != m_stropt_defs.end(); ++i ) {
        short_len = (*i).m_short_opt.length();
        long_len = (*i).m_long_opt.length();

        if ( arg.substr(0, short_len) == (*i).m_short_opt ) {
            m_stropts[(*i).m_name] = parse_stropt(arg, (*i).m_short_opt);
            found = true;
        } else if ( arg.substr(0, long_len) == (*i).m_long_opt ) {
            m_stropts[(*i).m_name] = parse_stropt(arg, (*i).m_long_opt);
            found = true;
        }
    }
    return found;
}


/*
 *  Processes a specified configuration file.
 *
 *  The method reads a text file, ignoring blank lines and lines
 *  beginning with a '#' symbol (i.e. comments).
 *
 *  Any line not containing an '=' character are stored, in their
 *  entirety, as a regular flag. Any line containing an '=' character
 *  is split at the first occurrence of '=', with the preceding part
 *  forming the key, and the following part forming the value, of a
 *  normal option. Values containing purely digits are automatically
 *  interpreted as integer options. All keys (for flags and options)
 *  and values (for string options) are stripped of leading and trailing
 *  whitespace.
 *
 *  Exceptions thrown:
 *    ConfigFileOpenFailed() if the config file cannot be opened.
 */

void CmdLineOptions::process_config_file() {
    string file_name = get_stropt_value(m_config_file_option);
    ifstream infile(file_name.c_str());

    if ( !infile ) {
        throw ConfigFileOpenFailed(file_name);
    }

    string line;
    while ( getline(infile, line) ) {
        pg_string::trim(line);
        size_t len = line.length();
        if ( !(len == 0 || line[0] == '#') ) {
            pair<string, string> kvpair = pg_string::get_key_value(line);
            if ( kvpair.second == "" ) {
                m_flags[kvpair.first] = true;
            } else {
                try {
                    int value = pg_string::stdstring_to_int(kvpair.second);
                    m_intopts[kvpair.first] = value;
                }
                catch(pg_string::BadValue) {
                    m_stropts[kvpair.first] = kvpair.second;
                }
            }
        }
    }
}


/*
 *  Shows a help message consisting of the program name and version
 *  number, followed by a list of all the recognized flags and options.
 */

void CmdLineOptions::show_help() const {
    assert(m_parse_called);
    show_version();
    cout << endl;
    show_all_options();
}


/*
 *  Shows the program name and version number, if they have been
 *  provided.
 */

void CmdLineOptions::show_version() const {
    assert(m_parse_called);
    if ( m_program_name != "" ) {
        string header = m_program_name;
        if ( m_version_number != "" ) {
            header = header + " (Version " + m_version_number + ")";
        }
        cout << header << endl;
    } else {
        cout << "No name or version information provided." << endl;
    }
}


/*
 *  Outputs a formatted list of all the flags and options recognized
 *  (i.e. for which definitions have been provided).
 *
 *  The flags and options are shown in alphabetical order by their names.
 *  The long and short versions of the options are shown (including
 *  placeholders for accepted integer or string arguments) along with
 *  a brief description.
 *
 *  As flags, integer options, and string options are stored separately,
 *  separate functions are called to retrieve maps of the name of each
 *  flag or option together with their formatted output. These maps
 *  are inserted into an overall map, which automatically sorts them
 *  by their key (i.e. by their name).
 */

void CmdLineOptions::show_all_options() const {
    assert(m_parse_called);
    map<string, string> opt_map, get_map;

    get_map = intopt_def_map();
    opt_map.insert(get_map.begin(), get_map.end());

    get_map = stropt_def_map();
    opt_map.insert(get_map.begin(), get_map.end());

    get_map = flag_def_map();
    opt_map.insert(get_map.begin(), get_map.end());

    cout << "Supported flags and options:" << endl;
    map<string, string>::iterator i;
    for ( i = opt_map.begin(); i != opt_map.end(); ++i ) {
        cout << "  " << (*i).first << ":" << endl;
        cout << "    " << (*i).second << endl;
    }
}


/*
 *  Returns a map of all recognized integer options (i.e. for which
 *  definitions have been provided) and a formatted string showing
 *  their usage.
 *
 *  Returns:
 *    a std::map<std::string std::string> where the first element is
 *    the name of the option, and the second element is a formatted
 *    string showing its usage.
 */

map<string, string> CmdLineOptions::intopt_def_map() const {
    assert(m_parse_called);
    map<string, string> return_map;
    IntOptDefList::const_iterator i;

    for ( i = m_intopt_defs.begin(); i != m_intopt_defs.end(); ++i ) {
        ostringstream oss;
        oss << (*i).m_short_opt << "N"
            << " or " << (*i).m_long_opt << "=N, "
            << (*i).m_description;
        if ( (*i).m_has_default ) {
            oss << " (default: " << (*i).m_default_value << ")";
        }
        return_map[(*i).m_name] = oss.str();
    }
    return return_map;
}


/*
 *  Returns a map of all recognized string options (i.e. for which
 *  definitions have been provided) and a formatted string showing
 *  their usage.
 *
 *  Returns:
 *    a std::map<std::string std::string> where the first element is
 *    the name of the option, and the second element is a formatted
 *    string showing its usage.
 */

map<string, string> CmdLineOptions::stropt_def_map() const {
    assert(m_parse_called);
    map<string, string> return_map;
    StrOptDefList::const_iterator i;

    for ( i = m_stropt_defs.begin(); i != m_stropt_defs.end(); ++i ) {
        ostringstream oss;
        oss << (*i).m_short_opt << "STR"
            << " or " << (*i).m_long_opt << "=STR, "
            << (*i).m_description;
        if ( (*i).m_has_default ) {
            oss << " (default: " << (*i).m_default_value << ")";
        }
        return_map[(*i).m_name] = oss.str();
    }
    return return_map;
}


/*
 *  Returns a map of all recognized flags (i.e. for which
 *  definitions have been provided) and a formatted string showing
 *  their usage.
 *
 *  Returns:
 *    a std::map<std::string std::string> where the first element is
 *    the name of the flag, and the second element is a formatted
 *    string showing its usage.
 */

map<string, string> CmdLineOptions::flag_def_map() const {
    assert(m_parse_called);
    map<string, string> return_map;
    FlagDefList::const_iterator i;

    for ( i = m_flag_defs.begin(); i != m_flag_defs.end(); ++i ) {
        ostringstream oss;
        oss << (*i).m_short_flag
            << " or " << (*i).m_long_flag << ", "
            << (*i).m_description;
        return_map[(*i).m_name] = oss.str();
    }
    return return_map;
}


/*  Returns the value part of an identified option provided on the
 *  command line. 
 *
 *  Arguments:
 *    arg -- the entire option string provided on the command line
 *    option -- the option identifier (e.g. '-d') which should equal
 *              the first part of arg.
 *  
 *  Returns:
 *    a string represent the value part of the option (i.e. anything
 *    after the first '=' character).
 *
 *  Exceptions thrown:
 *    MissingOptionValue() if there are no characters after the
 *      first '=' character, or no '=' character at all.
 */

string cmdline::parse_stropt(const string& arg, const string& option) {
    string value = arg.substr(option.length());

    if ( value.length() > 0 && value[0] == '=' ) {
        value = value.substr(1);
    }

    if ( value.length() == 0 ) {
        throw MissingOptionValue(option);
    }

    return value;
}


/*  Returns an integer formed by parsing the value of an identified
 *  integer option provided on the command line.
 *
 *  Arguments:
 *    arg -- the entire option string provided on the command line
 *    option -- the option identifier (e.g. '-d') which should equal
 *              the first part of arg.
 *           
 *  Exceptions thrown:
 *    BadOptionValue() if the value does not consist entirely of digits.
 */

int cmdline::parse_intopt(const string& arg, const string& option) {
    string value_str = parse_stropt(arg, option);
    int value;
    try {
       value = pg_string::stdstring_to_int(value_str);
    }
    catch(pg_string::BadValue) {
        throw BadOptionValue(option);
    }
    return value;
}

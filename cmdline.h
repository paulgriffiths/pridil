/*
 *  cmdline.h
 *  =========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  A general purpose command line argument and configuration file
 *  parsing class.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 *
 *
 *  GENERAL INSTRUCTIONS
 *  ====================
 *
 *  1. Create a CmdLineOptions instance.
 *  2. Optionally call the functions:
 *
 *       set_program_name()
 *       set_version_number()
 *       set_config_file_option()
 *       set_intopt()
 *       set_stropt()
 *       set_flag()
 *
 *     to set the program name and version number to be shown in the
 *     help message, and to set the flags (e.g. '-d' or '--detailed'),
 *     integer options (e.g. '-t4' or '--tabs=4') and string options
 *     (e.g. '-cmyconfigfile' or '--config-file=myconfigfile') that
 *     the program will accept. The set_config_file_option() optionally
 *     identifies the string option whose value will be interpreted
 *     as the file name of a configuration file.
 *
 *     The configuration file should be a text file with each line of the
 *     format 'key=value' or simply 'key'. Lines without a value will
 *     be interpreted as flags set on the command line, and lines with a
 *     value will be interpreted as options set on the command line. Values
 *     containing only digits will be automatically interpreted as integer
 *     options, and all others values will be interpreted as string options.
 *     Blank lines and lines beginning with a '#' character (i.e. comments)
 *     will be ignored. Trailing and leading whitespace for each line will
 *     be ignored, as will whitespace before and after the '=' character
 *     for a key/value pair.
 *
 *     Any command line arguments not matching defined flags or options
 *     will be stored in a retrievable list of 'positional arguments'.
 *
 *  3. Call parse() to parse the command line arguments and to parse the
 *     configuration file if one was provided. parse() automatically
 *     shows a help message detailing the flags and options recognized
 *     (based on the definitions provided in the previous step) if the
 *     '-h' or '--help' flags are specified on the command line, and
 *     the program name and version number if the '-v' or '--version'
 *     flags are specified on the command line. parse() returns false
 *     in either case and true otherwise, the caller will normally
 *     want to terminate the overall program when parse() returns
 *     false.
 *
 *  4. If desired, call the following methods:
 *
 *       is_flag_set()
 *       is_intopt_set()
 *       is_stropt_set()
 *       is_posarg_set()
 *
 *     to check whether a specified flag, option or positional argument
 *     was provided.
 *
 *   5. If desired, call the following methods:
 *
 *        get_intopt_value()
 *        get_stropt_value()
 *        get_pos_args()
 *
 *      to get the value of a specified integer or string argument, or
 *      to obtain a list of provided positional arguments.
 *
 *  Refer to the comments below and to cmdline.cpp for additional and
 *  more detailed comments on the individual methods.
 */


#ifndef PG_COMMAND_LINE_OPTIONS_V100_H
#define PG_COMMAND_LINE_OPTIONS_V100_H

#include <map>
#include <list>
#include <string>


namespace cmdline {

    //  Using declarations

    using std::string;
    using std::map;
    using std::list;


    //  Exception classes

    //  Base exception, all custom exceptions thrown by this module
    //  are derived from CmdLineException

    class CmdLineException {
        private:
            string m_error_message;

        public:
            explicit CmdLineException(const string& msg =
                                      "No error message")
                : m_error_message(msg) {}
            virtual ~CmdLineException() {}

            const string& what() const { return m_error_message; }
    };


    //  Thrown if argv[0] is not readable (rare)

    class BadExecutableName : public CmdLineException {
        public:
            BadExecutableName() : CmdLineException("Bad executable name") {}
    };


    //  Thrown if an option value is expected, but missing

    class MissingOptionValue : public CmdLineException {
        public:
            explicit MissingOptionValue(const string& option)
                : CmdLineException("Missing value for option " + option) {}
    };


    //  Thrown if an option value is provided, but in an incorrect format
    //  (e.g. if an expected integer option contains alphabetic
    //  characters)

    class BadOptionValue : public CmdLineException {
        public:
            explicit BadOptionValue(const string& option)
                : CmdLineException("Bad value for option " + option) {}
    };


    //  Thrown if the value of an option which has not been provided
    //  is requested

    class OptionNotProvided : public CmdLineException {
        public:
            explicit OptionNotProvided(const string& option)
                : CmdLineException("Option " + option + " not provided.") {}
    };


    //  Thrown when a specified configuration file cannot be opened

    class ConfigFileOpenFailed : public CmdLineException {
        public:
            explicit ConfigFileOpenFailed(const string& filename)
                : CmdLineException("Couldn't open config file " + filename) {}
    };


    //  Thrown when getter functions are called after parse()

    class ParseAlreadyCalled : public CmdLineException {
        public:
            explicit ParseAlreadyCalled(const string& func)
                : CmdLineException(func + " can't be called after parse()") {}
    };


    //  Thrown when setter functions are called before parse()

    class ParseNotCalled : public CmdLineException {
        public:
            explicit ParseNotCalled(const string& func)
                : CmdLineException(func + " can't be called before parse()") {}
    };


    //  Command line option definition structure

    template<class T>
    struct OptDef {
        const string m_name;
        const string m_short_opt;
        const string m_long_opt;
        const string m_description;
        const bool m_has_default;
        const T m_default_value;

        OptDef<T>(const string& name, const string& short_option,
                  const string& long_option,
                  const string& description,
                  const bool has_default,
                  const T& default_value)
            : m_name(name), m_short_opt(short_option),
              m_long_opt(long_option), m_description(description),
              m_has_default(has_default), m_default_value(default_value) {}
    };


    //  Command line flag definition structure

    struct FlagDef {
        const string m_name;
        const string m_short_flag;
        const string m_long_flag;
        const string m_description;
        const bool m_default_on;

        FlagDef(const string& name, const string& short_flag,
                const string& long_flag,
                const string& description,
                const bool default_on)
                : m_name(name), m_short_flag(short_flag),
                  m_long_flag(long_flag), m_description(description),
                  m_default_on(default_on) {}
    };


    //  Typedefs for options, flags and positional arguments

    typedef OptDef<int> IntOptDef;
    typedef list<IntOptDef> IntOptDefList;
    typedef map<string, int> IntOptMap;

    typedef OptDef<string> StrOptDef;
    typedef list<StrOptDef> StrOptDefList;
    typedef map<string, string> StrOptMap;

    typedef list<FlagDef> FlagDefList;
    typedef map<string, bool> FlagMap;

    typedef list<string> PosArgList;


    //  CmdLineOptions class

    class CmdLineOptions {
        public:

            //  Constructor

            CmdLineOptions();


            //  Methods for setting information and definitions
            //  for flags and options. These should be called
            //  before parse(), if they are called at all.

            void set_program_name(const string& program_name);
            void set_version_number(const string& version_number);
            void set_config_file_option(const string& option);
            void set_intopt(const string& name,
                            const string& short_option,
                            const string& long_option,
                            const string& description,
                            const bool has_default = false,
                            const int default_value = 0);
            void set_stropt(const string& name,
                            const string& short_option,
                            const string& long_option,
                            const string& description,
                            const bool has_default = false,
                            const string& default_value = "");
            void set_flag(const string& name,
                          const string& short_option,
                          const string& long_option,
                          const string& description,
                          const bool has_default = false);


            //  Main method for parsing command line arguments in
            //  accordance with provided settings. This should be
            //  called only once.

            bool parse(const int argc, char const* const* argv);


            //  Methods for checking whether specified flags, options
            //  or positional argumentsare set. These should be called
            //  after calling parse(), if they are called at all.

            bool is_flag_set(const string& name) const;
            bool is_intopt_set(const string& option) const;
            bool is_stropt_set(const string& option) const;
            bool is_posarg_set(const string& option) const;


            //  Methods for obtaining the values of provided options
            //  and positional arguments. These should be called
            //  after calling parse(), if they are called at all.

            int get_intopt_value(const string& name) const;
            string get_stropt_value(const string& name) const;
            const list<string>& get_pos_args() const;

        private:

            //  General member variables

            string m_program_name;
            string m_version_number;
            string m_executable_name;
            string m_config_file_option;


            //  Data structures for storing options, flags and
            //  their definitions, and for storing positional arguments

            IntOptDefList m_intopt_defs;
            StrOptDefList m_stropt_defs;
            FlagDefList m_flag_defs;

            IntOptMap m_intopts;
            StrOptMap m_stropts;
            FlagMap m_flags;
            PosArgList m_posargs;


            //  Status flags

            bool m_parse_called;


            //  Methods for processing flags, options, and a specified
            //  configuration file, called by parse()

            bool check_arg_for_flag(const string& arg);
            bool check_arg_for_intopt(const string& arg);
            bool check_arg_for_stropt(const string& arg);
            void process_config_file();


            //  Methods to show help and version messages

            void show_help() const;
            void show_version() const;


            //  Methods for showing the list of defined flags
            //  and options, called by show_help()

            void show_all_options() const;
            map<string, string> intopt_def_map() const;
            map<string, string> stropt_def_map() const;
            map<string, string> flag_def_map() const;
    };


    //  Standalone helper function declarations

    string parse_stropt(const string& arg,
                        const string& option);
    int parse_intopt(const string& arg, const string& option);

}

#endif      // PG_COMMAND_LINE_OPTIONS_V100_H

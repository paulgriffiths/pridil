/*
 *  main.cpp
 *  ========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Entry point to for Prisoners' Dilemma simulation.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cctype>

#include "pridil.h"
#include "cmdline.h"


namespace {

    /*
     *  Struct for storing command line display options.
     */

    struct DisplayOptions {
    bool m_detailed_memories;
    bool m_summary_creatures;
    bool m_summary_resources;

    DisplayOptions() :
        m_detailed_memories(false),
        m_summary_creatures(false),
        m_summary_resources(false) {}
    };

}


/*
 *  Forward function declarations
 */

bool ParseCmdLine(const int argc, char const* const* argv,
                  pridil::WorldInfo& wInfo,
                  DisplayOptions& dOptions);


/*
 *  main() function
 */

int main(int argc, char ** argv) {
    pridil::WorldInfo wInfo;
    DisplayOptions dOptions;

    //  Get command line and config file options

    try {
        if ( !ParseCmdLine(argc, argv, wInfo, dOptions) ) {
            return 0;
        }
    } catch(...) {
        return 1;
    }

    //  Initialize and run world.

    pridil::World world(wInfo);
    for ( int i = 0; i < wInfo.m_days_to_run; ++i ) {
        world.advance_day();
    }


    //  Output statistics

    world.output_world_stats(std::cout);
    if ( dOptions.m_detailed_memories ) {
        world.output_full_creature_stats(std::cout);
    }
    if ( dOptions.m_summary_creatures ) {
        world.output_summary_creature_stats(std::cout);
    }
    if ( dOptions.m_summary_resources ) {
        world.output_summary_resources_by_strategy(std::cout);
        world.output_summary_dead_by_strategy(std::cout);
    }
    return 0;
}


namespace {

    /*
     *  Parse command line info for options.
     *
     *  Option structure is used to make populating the WorldInfo structure
     *  easier, i.e. so the population can be performed within a loop.
     */

    template<class T>
    struct Option {
        std::string name;
        T * location;
        T default_value;

        Option<T>(std::string n, T * l, T d)
            : name(n), location(l), default_value(d) {}

        //  Override copy constructor and operator= because we
        //  have a struct with a pointer member. In this case, we
        //  really do just want to copy the pointer, so we'd have
        //  been fine with the defaults, but it's a good practice to
        //  provide them and to eliminate deliberately-restrictive
        //  compiler warnings.

        Option<T>(const Option<T>& opt)
            : name(opt.name), location(opt.location),
              default_value(opt.default_value) {}

        Option<T>& operator=(const Option<T>& opt) {
            name = opt.name;
            location = opt.location;
            default_value = opt.default_value;
            return *this;
        }
    };

}


/*
 *  Parses command line options using the CmdLineOptions module and
 *  sets appropriate display and world information properties.
 */

bool ParseCmdLine(const int argc, char const* const* argv,
                  pridil::WorldInfo& wInfo,
                  DisplayOptions& dOptions) {

    //  Create CmdLineOptions object and set flags & options

    cmdline::CmdLineOptions opts;
    opts.set_program_name("Prisoners' Dilemma Simulation");
    opts.set_version_number("0.9");
    opts.set_flag("detailed memories", "-d", "--detailedmemory",
                  "show detailed creature memories", false);
    opts.set_flag("summary resources", "-r", "--summaryresources",
                  "show summary resources by strategy", false);
    opts.set_flag("summary creatures", "-s", "--summarycreatures",
                  "show summary creature statistics", false);
    opts.set_flag("disable deaths", "-D", "--disabledeaths",
                  "disable death of creatures when resources expire", false);
    opts.set_flag("disable reproduction", "-R", "--disablerepro",
                  "disable reproduction of creatures", false);
    opts.set_intopt("days_to_run", "-y", "--daystorun",
                    "specify number of days to run", true, 100);
    opts.set_stropt("configfile", "-c", "--configfile",
                    "provides the location of a configuration file",
                     false, "");
    opts.set_config_file_option("configfile");

    try {
        if ( !opts.parse(argc, argv) ) {
            return false;
        }
    }
    catch(cmdline::CmdLineException& exc) {
        std::cerr << exc.what() << std::endl;
        throw;
    }


    //  Populate WorldInfo struct based on options provided

    std::list<Option<int> > iol;

    iol.push_back(Option<int>("random_strategy", &wInfo.m_random_strategy, 0));
    iol.push_back(Option<int>("tit_for_tat", &wInfo.m_tit_for_tat, 0));
    iol.push_back(Option<int>("tit_for_two_tats",
                              &wInfo.m_tit_for_two_tats, 0));
    iol.push_back(Option<int>("susp_tit_for_tat",
                              &wInfo.m_susp_tit_for_tat, 0));
    iol.push_back(Option<int>("naive_prober", &wInfo.m_naive_prober, 0));
    iol.push_back(Option<int>("always_cooperate",
                              &wInfo.m_always_cooperate, 0));
    iol.push_back(Option<int>("always_defect", &wInfo.m_always_defect, 0));
    iol.push_back(Option<int>("default_starting_resources",
                              &wInfo.m_default_starting_resources, 100));
    iol.push_back(Option<int>("repro_cost",
                              &wInfo.m_repro_cost, 50));
    iol.push_back(Option<int>("repro_min_resources",
                              &wInfo.m_repro_min_resources, 75));

    std::list<Option<int> >::iterator i;
    int opt_val;
    for ( i = iol.begin(); i != iol.end(); ++i ) {
        try {
            opt_val = opts.get_intopt_value((*i).name);
        } catch(cmdline::OptionNotProvided) {
            opt_val = (*i).default_value;
        }
        *((*i).location) = opt_val;
    }


    std::list<Option<pridil::Day> > dol;
    dol.push_back(Option<pridil::Day>("default_life_expectancy",
                              &wInfo.m_default_life_expectancy, 10000));
    dol.push_back(Option<pridil::Day>("default_life_expectancy_range",
                              &wInfo.m_default_life_expectancy_range, 0));
    dol.push_back(Option<pridil::Day>("days_to_run",
                              &wInfo.m_days_to_run, 100));
    dol.push_back(Option<pridil::Day>("repro_cycle_days",
                              &wInfo.m_repro_cycle_days, 10));

    std::list<Option<pridil::Day> >::iterator d;
    pridil::Day day_val;
    for ( d = dol.begin(); d != dol.end(); ++d ) {
        try {
            day_val = opts.get_intopt_value((*d).name);
        } catch(cmdline::OptionNotProvided) {
            day_val = (*d).default_value;
        }
        *((*d).location) = day_val;
    }


    //  Populate WorldInfo struct based on flags provided

    wInfo.m_disable_deaths = opts.is_flag_set("disable deaths");
    wInfo.m_disable_repro = opts.is_flag_set("disable reproduction");


    //  Populate DisplayOptions struct based on flags provided

    dOptions.m_detailed_memories = opts.is_flag_set("detailed memories");
    dOptions.m_summary_creatures = opts.is_flag_set("summary creatures");
    dOptions.m_summary_resources = opts.is_flag_set("summary resources");

    return true;
}

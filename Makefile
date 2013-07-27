# Prisoners' Dilemma Evolution Simulator -- Makefile
# ==================================================
# Copyright 2013 Paul Griffiths
# Email: mail@paulgriffiths.net
#
# Distributed under the terms of the GNU General Public License.
# http://www.gnu.org/licenses/


# Variables section
# =================

# Executable names
OUT=pridil
TESTOUT=unittests

# Compiler executable name
CXX=g++

# Compiler flags
CXXFLAGS=-ansi -pedantic -Wall -Wextra -Weffc++
CXX_DEBUG_FLAGS=-ggdb -DDEBUG -DDEBUG_ALL
CXX_RELEASE_FLAGS=-O3 -DNDEBUG
CXX_PROFILE_FLAGS=-fprofile-arcs -ftest-coverage -pg

# Linker flags
LDFLAGS=
LD_TEST_FLAGS=-lCppUTest -lCppUTestExt

# Object code files
MAINOBJ=main.o
TESTMAINOBJ=unittests.o

OBJS=cmdline.o creature.o dna.o game.o
OBJS+=memory.o world.o pg_string_helpers.o

TESTOBJS=test_cmdline_intopt.o test_cmdline_parse_order.o
TESTOBJS+=test_cmdline_stropt.o test_cmdline_flag.o test_cmdline_posarg.o
TESTOBJS+=test_pg_string.o test_cmdline_configfile.o
TESTOBJS+=test_cmdline_parsereturn.o

# Unused
# SRCS=$(wildcard *.cpp)
# TESTSRCS=$(wildcard tests/*.cpp)


# Build targets section
# =====================

default: main

# debug - builds objects with debugging info
.PHONY: debug
debug: CXXFLAGS+=$(CXX_DEBUG_FLAGS)
debug: main

# release - builds with optimizations and without debugging info
.PHONY: release
release: CXXFLAGS+=$(CXX_RELEASE_FLAGS)
release: main

# profile - builds with information for gcov and gprof tools
.PHONY: profile
profile: CXXFLAGS+=$(CXX_PROFILE_FLAGS)
profile: main

# tests - builds unit tests
.PHONY: tests
tests: CXXFLAGS+=$(CXX_RELEASE_FLAGS)
tests: LDFLAGS+=$(LD_TEST_FLAGS)
tests: testmain

# clean - removes ancilliary files from working directory
.PHONY: clean
clean:
	-rm *~ *.o *.gcov *.out *.gcda *.gcno

# lint - runs cpplint with specified options
.PHONY: lint
lint:
	cpplint --filter=-runtime/references,-build/header_guard,\
-readability/streams,-build/include,-legal/copyright,\
-runtime/threadsafe_fn,-whitespace/blank_line,-runtime/int \
*.cpp *.h tests/*.cpp

# check - runs cppcheck with specified options
.PHONY: check
check:
	cppcheck --enable=all *.cpp *.h tests/*.cpp


# Executable targets section
# ==========================

# Main executable
main: $(MAINOBJ) $(OBJS)
	$(CXX) -o $(OUT) $(MAINOBJ) $(OBJS) $(LDFLAGS) 

# Unit tests executable
testmain: $(TESTMAINOBJ) $(TESTOBJS) $(OBJS)
	$(CXX) -o $(TESTOUT) $(TESTMAINOBJ) $(TESTOBJS) $(OBJS) $(LDFLAGS) 


# Object files targets section
# ============================

main.o: main.cpp world.h cmdline.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

cmdline.o: cmdline.cpp cmdline.h pg_string_helpers.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

creature.o: creature.cpp creature.h dna.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

dna.o: dna.cpp dna.h game.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

game.o: game.cpp game.h 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

memory.o: memory.cpp memory.h game.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

world.o: world.cpp world.h creature.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

pg_string_helpers.o: pg_string_helpers.cpp pg_string_helpers.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

unittests.o: tests/testmain.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test_cmdline_intopt.o: tests/test_cmdline_intopt.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test_cmdline_parse_order.o: tests/test_cmdline_parse_order.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test_cmdline_stropt.o: tests/test_cmdline_stropt.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test_cmdline_flag.o: tests/test_cmdline_flag.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test_cmdline_posarg.o: tests/test_cmdline_posarg.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test_pg_string.o: tests/test_pg_string.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test_cmdline_configfile.o: tests/test_cmdline_configfile.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test_cmdline_parsereturn.o: tests/test_cmdline_parsereturn.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<


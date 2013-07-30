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
TESTMAINOBJ=tests/unittests.o

OBJS=cmdline.o creature.o dna.o game.o brain.o
OBJS+=memory.o world.o pg_string_helpers.o
OBJS+=genes/strategy_gene.o genes/strategy/always_cooperate_gene.o
OBJS+=genes/strategy/always_defect_gene.o genes/strategy/random_strategy_gene.o
OBJS+=genes/strategy/tit_for_tat_gene.o genes/strategy/susp_tit_for_tat_gene.o
OBJS+=genes/strategy/tit_for_two_tats_gene.o genes/strategy/naive_prober_gene.o

TESTOBJS=tests/test_cmdline/test_cmdline_intopt.o
TESTOBJS+=tests/test_cmdline/test_cmdline_parse_order.o
TESTOBJS+=tests/test_cmdline/test_cmdline_stropt.o
TESTOBJS+=tests/test_cmdline/test_cmdline_flag.o
TESTOBJS+=tests/test_cmdline/test_cmdline_posarg.o
TESTOBJS+=tests/test_cmdline/test_cmdline_configfile.o
TESTOBJS+=tests/test_cmdline/test_cmdline_parsereturn.o
TESTOBJS+=tests/test_pg_string/test_pg_string.o
TESTOBJS+=tests/test_genes/test_titfortatgene.o
TESTOBJS+=tests/test_genes/test_susptitfortatgene.o
TESTOBJS+=tests/test_genes/test_alwayscooperategene.o
TESTOBJS+=tests/test_genes/test_alwaysdefectgene.o
TESTOBJS+=tests/test_genes/test_randomstrategygene.o
TESTOBJS+=tests/test_genes/test_naiveprobergene.o
TESTOBJS+=tests/test_game/test_simplify_game_move.o
TESTOBJS+=tests/test_game/test_game_result.o
TESTOBJS+=tests/test_memory/test_store_memory.o
TESTOBJS+=tests/test_memory/test_recognize.o
TESTOBJS+=tests/test_memory/test_num_memories.o
TESTOBJS+=tests/test_creature/test_creature_battle.o

# Source and clean files and globs
SRCS=$(wildcard *.cpp *.h)
SRCS+=$(wildcard genes/*.cpp genes/*.h)
SRCS+=$(wildcard genes/strategy/*.cpp genes/strategy/*.h)
SRCS+=$(wildcard tests/*.cpp tests/*.h)
SRCS+=$(wildcard tests/test_cmdline/*.cpp tests/test_cmdline/*.h)
SRCS+=$(wildcard tests/test_genes/*.cpp tests/test_genes/*.h)
SRCS+=$(wildcard tests/test_game/*.cpp tests/test_game/*.h)
SRCS+=$(wildcard tests/test_memory/*.cpp tests/test_memory/*.h)
SRCS+=$(wildcard tests/test_creature/*.cpp tests/test_creature/*.h)
SRCS+=$(wildcard tests/test_pg_string/*.cpp tests/test_pg_string/*.h)

SRCGLOB=*.cpp *.h
SRCGLOB+=genes/*.cpp genes/*.h
SRCGLOB+=genes/strategy/*.cpp genes/strategy/*.h
SRCGLOB+=tests/*.cpp tests/*.h
SRCGLOB+=tests/test_cmdline/*.cpp tests/test_cmdline/*.h
SRCGLOB+=tests/test_genes/*.cpp tests/test_genes/*.h
SRCGLOB+=tests/test_game/*.cpp tests/test_game/*.h
SRCGLOB+=tests/test_memory/*.cpp tests/test_memory/*.h
SRCGLOB+=tests/test_creature/*.cpp tests/test_creature/*.h
SRCGLOB+=tests/test_pg_string/*.cpp tests/test_pg_string/*.h

CLNGLOB=pridil unittests
CLNGLOB+=*~ *.o *.gcov *.out *.gcda *.gcno
CLNGLOB+=genes/*~ genes/*.o genes/*.gcov genes/*.out genes/*.gcda genes/*.gcno
CLNGLOB+=genes/strategy/*~ genes/strategy/*.o
CLNGLOB+=genes/strategy/*.gcov genes/strategy/*.out
CLNGLOB+=genes/strategy/*.gcda genes/strategy/*.gcno
CLNGLOB+=tests/*~ tests/*.o tests/*.gcov tests/*.out tests/*.gcda tests/*.gcno
CLNGLOB+=tests/test_cmdline/*~ tests/test_cmdline/*.o
CLNGLOB+=tests/test_cmdline/*.gcov tests/test_cmdline/*.out
CLNGLOB+=tests/test_cmdline/*.gcda tests/test_cmdline/*.gcno
CLNGLOB+=tests/test_genes/*~ tests/test_genes/*.o
CLNGLOB+=tests/test_genes/*.gcov tests/test_genes/*.out
CLNGLOB+=tests/test_genes/*.gcda tests/test_genes/*.gcno
CLNGLOB+=tests/test_pg_string/*~ tests/test_pg_string/*.o
CLNGLOB+=tests/test_pg_string/*.gcov tests/test_pg_string/*.out
CLNGLOB+=tests/test_pg_string/*.gcda tests/test_pg_string/*.gcno
CLNGLOB+=tests/test_game/*~ tests/test_game/*.o
CLNGLOB+=tests/test_game/*.gcov tests/test_game/*.out
CLNGLOB+=tests/test_game/*.gcda tests/test_game/*.gcno
CLNGLOB+=tests/test_memory/*~ tests/test_memory/*.o
CLNGLOB+=tests/test_memory/*.gcov tests/test_memory/*.out
CLNGLOB+=tests/test_memory/*.gcda tests/test_memory/*.gcno
CLNGLOB+=tests/test_creature/*~ tests/test_creature/*.o
CLNGLOB+=tests/test_creature/*.gcov tests/test_creature/*.out
CLNGLOB+=tests/test_creature/*.gcda tests/test_creature/*.gcno


# Build targets section
# =====================

default: debug

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
tests: CXXFLAGS+=$(CXX_DEBUG_FLAGS)
tests: LDFLAGS+=$(LD_TEST_FLAGS)
tests: testmain

# clean - removes ancilliary files from working directory
.PHONY: clean
clean:
	-@rm $(CLNGLOB) 2>/dev/null

# lint - runs cpplint with specified options
.PHONY: lint
lint:
	@cpplint --verbose=5 --filter=-runtime/references,-build/header_guard,\
-readability/streams,-build/include,-legal/copyright,\
-runtime/threadsafe_fn,-whitespace/blank_line,-runtime/int,\
-build/namespaces \
$(SRCGLOB)

# check - runs cppcheck with specified options
.PHONY: check
check:
	@cppcheck --enable=all $(SRCGLOB)


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

# Main program

main.o: main.cpp pridil.h cmdline.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

cmdline.o: cmdline.cpp cmdline.h pg_string_helpers.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

creature.o: creature.cpp creature.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

brain.o: brain.cpp brain_complex.h game.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

dna.o: dna.cpp brain_complex.h game.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

game.o: game.cpp game.h 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

memory.o: memory.cpp brain_complex.h game.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

world.o: world.cpp world.h creature.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

pg_string_helpers.o: pg_string_helpers.cpp pg_string_helpers.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

genes/strategy_gene.o: genes/strategy_gene.cpp \
		genes/strategy_gene.h genes/strategy_gene.h \
		genes/gene.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

genes/strategy/always_cooperate_gene.o: \
		genes/strategy/always_cooperate_gene.cpp \
		genes/strategy/always_cooperate_gene.h \
		genes/strategy_gene.h \
		genes/gene.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

genes/strategy/always_defect_gene.o: \
		genes/strategy/always_defect_gene.cpp \
		genes/strategy/always_defect_gene.h \
		genes/strategy_gene.h \
		genes/gene.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

genes/strategy/random_strategy_gene.o: \
		genes/strategy/random_strategy_gene.cpp \
		genes/strategy/random_strategy_gene.h \
		genes/strategy_gene.h \
		genes/gene.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

genes/strategy/tit_for_tat_gene.o: \
		genes/strategy/tit_for_tat_gene.cpp \
		genes/strategy/tit_for_tat_gene.h \
		genes/strategy_gene.h \
		genes/gene.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

genes/strategy/susp_tit_for_tat_gene.o: \
		genes/strategy/susp_tit_for_tat_gene.cpp \
		genes/strategy/susp_tit_for_tat_gene.h \
		genes/strategy_gene.h \
		genes/gene.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

genes/strategy/tit_for_two_tats_gene.o: \
		genes/strategy/tit_for_two_tats_gene.cpp \
		genes/strategy/tit_for_two_tats_gene.h \
		genes/strategy_gene.h \
		genes/gene.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

genes/strategy/naive_prober_gene.o: \
		genes/strategy/naive_prober_gene.cpp \
		genes/strategy/naive_prober_gene.h \
		genes/strategy_gene.h \
		genes/gene.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<


# Unit tests

tests/unittests.o: tests/testmain.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_cmdline/test_cmdline_intopt.o: \
	tests/test_cmdline/test_cmdline_intopt.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_cmdline/test_cmdline_parse_order.o: \
	tests/test_cmdline/test_cmdline_parse_order.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_cmdline/test_cmdline_stropt.o: \
	tests/test_cmdline/test_cmdline_stropt.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_cmdline/test_cmdline_flag.o: \
	tests/test_cmdline/test_cmdline_flag.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_cmdline/test_cmdline_posarg.o: \
	tests/test_cmdline/test_cmdline_posarg.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_pg_string/test_pg_string.o: \
	tests/test_pg_string/test_pg_string.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_cmdline/test_cmdline_configfile.o: \
	tests/test_cmdline/test_cmdline_configfile.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_cmdline/test_cmdline_parsereturn.o: \
	tests/test_cmdline/test_cmdline_parsereturn.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_genes/cmdline/test_titfortatgene.o: \
	tests/test_genes/test_titfortatgene.cpp brain_complex.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_genes/test_susptitfortatgene.o: \
	tests/test_genes/test_susptitfortatgene.cpp brain_complex.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_genes/test_alwayscooperategene.o: \
	tests/test_genes/test_alwayscooperategene.cpp brain_complex.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_genes/test_alwaysdefectgene.o: \
	tests/test_genes/test_alwaysdefectgene.cpp brain_complex.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_genes/test_randomstrategygene.o: \
	tests/test_genes/test_randomstrategygene.cpp brain_complex.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_genes/test_naiveprobergene.o: \
	tests/test_genes/test_naiveprobergene.cpp brain_complex.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_game/test_simplify_game_move.o: \
	tests/test_game/test_simplify_game_move.cpp game.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_game/test_game_result.o: \
	tests/test_game/test_game_result.cpp game.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_memory/test_store_memory.o: \
	tests/test_memory/test_store_memory.cpp game.h brain_complex.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_memory/test_recognize.o: \
	tests/test_memory/test_recognize.cpp game.h brain_complex.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_memory/test_num_memories.o: \
	tests/test_memory/test_num_memories.cpp game.h brain_complex.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_creature/test_creature_battle.o: \
	tests/test_creature/test_creature_battle.cpp creature.h game.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<



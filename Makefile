OUT=pridil
TESTOUT=unittests
SRCS=$(wildcard *.cpp)
TESTSRCS=$(wildcard tests/*.cpp)
MAINOBJ=main.o
TESTMAINOBJ=unittests.o
OBJS=cmdline.o creature.o dna.o game.o
OBJS+=memory.o world.o pg_string_helpers.o
TESTOBJS=testcmdline.o
CXX=g++
LDFLAGS=
CXXFLAGS=-ansi -pedantic -Wall -Wextra -Weffc++
CXX_DEBUG_FLAGS=-ggdb -DDEBUG -DDEBUG_ALL
CXX_RELEASE_FLAGS=-O3 -DNDEBUG
PROFILE_FLAGS=-fprofile-arcs -ftest-coverage -pg
LD_TEST_FLAGS=-lCppUTest -lCppUTestExt

default: main

.PHONY: debug
debug: CXXFLAGS+=$(CXX_DEBUG_FLAGS)
debug: main

.PHONY: release
release: CXXFLAGS+=$(CXX_RELEASE_FLAGS)
release: main

.PHONY: profile
profile: CXXFLAGS+=$(PROFILE_FLAGS)
profile: main

.PHONY: tests
tests: LDFLAGS+=$(LD_TEST_FLAGS)
tests: testmain

main: $(MAINOBJ) $(OBJS)
	$(CXX) -o $(OUT) $(MAINOBJ) $(OBJS) $(LDFLAGS) 

testmain: $(TESTMAINOBJ) $(TESTOBJS) $(OBJS)
	$(CXX) -o $(TESTOUT) $(TESTMAINOBJ) $(TESTOBJS) $(OBJS) $(LDFLAGS) 

main.o: main.cpp world.h cmdline.h
	$(CXX) $(CXXFLAGS) -c -o main.o main.cpp

cmdline.o: cmdline.cpp cmdline.h pg_string_helpers.h
	$(CXX) $(CXXFLAGS) -c -o cmdline.o cmdline.cpp

creature.o: creature.cpp creature.h dna.h
	$(CXX) $(CXXFLAGS) -c -o creature.o creature.cpp

dna.o: dna.cpp dna.h game.h
	$(CXX) $(CXXFLAGS) -c -o dna.o dna.cpp

game.o: game.cpp game.h 
	$(CXX) $(CXXFLAGS) -c -o game.o game.cpp

memory.o: memory.cpp memory.h game.h
	$(CXX) $(CXXFLAGS) -c -o memory.o memory.cpp

world.o: world.cpp world.h creature.h
	$(CXX) $(CXXFLAGS) -c -o world.o world.cpp

pg_string_helpers.o: pg_string_helpers.cpp pg_string_helpers.h
	$(CXX) $(CXXFLAGS) -c -o pg_string_helpers.o pg_string_helpers.cpp

unittests.o: tests/testmain.cpp
	$(CXX) $(CXXFLAGS) -c -o unittests.o tests/testmain.cpp

testcmdline.o: tests/testcmdline.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c -o testcmdline.o tests/testcmdline.cpp


.PHONY: clean
clean:
	-rm *~ *.o *.gcov *.out *.gcda *.gcno

.PHONY: indent
indent:
	indent *.cpp *.h

.PHONY: lint
lint:
	cpplint --filter=-runtime/references,-build/header_guard,-readability/streams,-build/include,-legal/copyright,-runtime/threadsafe_fn,-whitespace/blank_line,-runtime/int *.cpp *.h

.PHONY: check
check:
	cppcheck --enable=all *.cpp *.h

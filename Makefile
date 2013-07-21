OUT=pridil
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
CXX=g++
LDFLAGS=
CXXFLAGS=-ansi -pedantic -Wall -Wextra -Weffc++
CXX_DEBUG_FLAGS=-ggdb -DDEBUG -DDEBUG_ALL
CXX_RELEASE_FLAGS=-O3 -DNDEBUG
PROFILE_FLAGS=-fprofile-arcs -ftest-coverage -pg

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

main: cmdline.o creature.o dna.o game.o main.o memory.o world.o pg_string_helpers.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(OUT) cmdline.o creature.o dna.o game.o main.o memory.o world.o pg_string_helpers.o

main.o: main.cpp world.h cmdline.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c -o main.o main.cpp

cmdline.o: cmdline.cpp cmdline.h pg_string_helpers.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c -o cmdline.o cmdline.cpp

creature.o: creature.cpp creature.h dna.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c -o creature.o creature.cpp

dna.o: dna.cpp dna.h game.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c -o dna.o dna.cpp

game.o: game.cpp game.h 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c -o game.o game.cpp

memory.o: memory.cpp memory.h game.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c -o memory.o memory.cpp

world.o: world.cpp world.h creature.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c -o world.o world.cpp

pg_string_helpers.o: pg_string_helpers.cpp pg_string_helpers.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c -o pg_string_helpers.o pg_string_helpers.cpp


.PHONY: clean
clean:
	-rm *~ *.o *.gcov *.out *.gcda *.gcno

.PHONY: indent
indent:
	indent *.cpp *.h

.PHONY: lint
lint:
	cpplint --filter=-runtime/references,-build/header_guard,-readability/streams,-build/include,-legal/copyright,-runtime/threadsafe_fn,-whitespace/blank_line *.cpp *.h

.PHONY: check
check:
	cppcheck --enable=all *.cpp *.h


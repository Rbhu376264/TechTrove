CXX=g++
CXXFLAGS=-g -Wall -std=c++11 
# Uncomment for parser DEBUG
#DEFS=-DDEBUG


all: gridpaths sat_solver

gridpaths: gridpaths.cpp 
	$(CXX) $(CXXFLAGS) $(DEFS) $< -o $@

# Brute force recompile all files each time
# internal-range-test: internal-range-test.cpp internal-range.cpp internal-range.h
sat_solver: sat_solver.cpp avlbst.h bst.h print_bst.h
	$(CXX) $(CXXFLAGS) $(DEFS) $< -o $@


clean:
	rm -f *~ *.o gridpaths sat_solver
	
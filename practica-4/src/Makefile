# ------------------------------------
# Makefile para compilar la práctica 4
# -------------------------------------

PROG := main
SRCS :=  main.cc filesystem.cc shell.cc
CXX := g++
CXXFLAGS := -O2 -Wall -std=c++23 -pedantic

all: $(PROG)

$(PROG): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(PROG) -lstdc++exp

clean:
	rm -f $(PROG)

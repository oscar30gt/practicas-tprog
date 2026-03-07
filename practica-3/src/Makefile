# ------------------------------------
# Makefile para compilar la práctica 3
# -------------------------------------

PROG := main
SRCS :=  main.cc transportables.cc elemento.cc
CXX := g++
CXXFLAGS := -O2 -Wall -std=c++20

all: $(PROG)

$(PROG): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(PROG)

clean:
	rm -f $(PROG)

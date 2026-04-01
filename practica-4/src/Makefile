# ------------------------------------
# Makefile para compilar la práctica 4
# -------------------------------------

PROG := main
TEST := test
SRCS_PROG := main.cc
SRCS_TEST := test.cc
SRCS := filesystem.cc shell.cc
CXX := g++
CXXFLAGS := -O2 -Wall -std=c++23 -pedantic

all: $(PROG)

test: $(TEST)

$(PROG): $(SRCS_PROG) $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS_PROG) $(SRCS) -o $(PROG) -lstdc++exp

$(TEST): $(SRCS_TEST) $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS_TEST) $(SRCS) -o $(TEST) -lstdc++exp

clean:
	rm -f $(PROG) $(TEST)

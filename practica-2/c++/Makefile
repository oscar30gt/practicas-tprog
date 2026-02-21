PROG := main
SRCS := Instruction.cc Program.cc main.cc
CXX := g++ -O2
CXXFLAGS := -Wall

all: $(PROG)

$(PROG): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(PROG)

clean:
	rm -f $(PROG)

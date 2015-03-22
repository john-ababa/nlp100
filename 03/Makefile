.PHONY: all clean
.SUFFIXES: .cpp .o

CXX = g++
CXXFLAGS = -O3 -Wall -Wextra -std=c++11
PROGRAM = 20 21 22 23 24 25 26
all: $(PROGRAM)

20: 20.o
20.o: 20.cpp
21: 21.o
21.o: 21.cpp
22: 22.o
22.o: 22.cpp
23: 23.o
23.o: 23.cpp
24: 24.o
24.o: 24.cpp
25: 25.o
25.o: 25.cpp
26: 26.o
26.o: 26.cpp

## 適当
clean:
	rm -f $(PROGRAM) *.o
.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $<
%:
	$(CXX) $(CXXFLAGS) -o $@ $^

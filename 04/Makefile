.PHONY: all clean
.SUFFIXES: .cpp .o

CXX = g++
CXXFLAGS = -O3 -Wall -Wextra -std=c++11
LDLIB = -L$(HOME)/loacal/lib -lcabocha
PROGRAM = 40 41 42 43
all: $(PROGRAM)

40: 40.o
40.o: 40.cpp
41: 41.o
41.o: 41.cpp
42: 42.o
42.o: 42.cpp
43: 43.o
43.o: 43.cpp

## 適当
clean:
	rm -f $(PROGRAM) *.o
.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $<
%:
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIB)

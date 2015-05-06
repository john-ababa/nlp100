.PHONY: all clean
.SUFFIXES: .cpp .o

CXX = g++
CXXFLAGS = -O3 -Wall -Wextra -std=c++11
LDLIB = -L$(HOME)/loacal/lib -lcabocha
PROGRAM = 40 41 42 43 44 45 46 47 48
all: $(PROGRAM)

40: 40.o
40.o: 40.cpp
41: 41.o
41.o: 41.cpp
42: 42.o
42.o: 42.cpp
43: 43.o
43.o: 43.cpp
44: 44.o
44.o: 44.cpp
45: 45.o
45.o: 45.cpp
46: 46.o
46.o: 46.cpp
47: 47.o
47.o: 46.cpp
48: 48.o
48.o: 48.cpp

## 適当
clean:
	rm -f $(PROGRAM) *.o
.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $<
%:
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIB)

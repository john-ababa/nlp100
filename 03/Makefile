.PHONY: all clean
.SUFFIXES: .cpp .o

CXX = g++
CXXFLAGS = -O3 -Wall -Wextra -std=c++11
LDLIB = -L$(HOME)/loacal/lib -lmecab
PROGRAM = 30 31 32 33 34 35 36 37 38
all: $(PROGRAM)

30: 30.o common.o
30.o: 30.cpp
31: 31.o common.o
31.o: 31.cpp
32: 32.o common.o
32.o: 32.cpp
33: 33.o common.o
33.o: 33.cpp
34: 34.o common.o
34.o: 34.cpp
35: 35.o common.o
35.o: 35.cpp
36: 36.o common.o
36.o: 36.cpp
37: 37.o common.o
37.o: 37.cpp
38: 38.o common.o
38.o: 38.cpp
common.o: common.cpp

## 適当
clean:
	rm -f $(PROGRAM) *.o
.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $<
%:
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIB)

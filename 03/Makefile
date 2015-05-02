.PHONY: all clean
.SUFFIXES: .cpp .o

CXX = g++
CXXFLAGS = -O3 -Wall -Wextra -std=c++11
LDLIB = -L$(HOME)/loacal/lib -lmecab
PROGRAM = 30 31 32 33
all: $(PROGRAM)

30: 30.o common.o
30.o: 30.cpp
31: 31.o common.o
31.o: 31.cpp
32: 32.o common.o
32.o: 32.cpp
33: 33.o common.o
33.o: 33.cpp
common.o: common.cpp

## 適当
clean:
	rm -f $(PROGRAM) *.o
.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $<
%:
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIB)

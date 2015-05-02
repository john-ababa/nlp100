.PHONY: all clean
.SUFFIXES: .cpp .o

CXX = g++
CXXFLAGS = -O3 -Wall -Wextra -std=c++11
LDLIB = -L$(HOME)/loacal/lib -lmecab
PROGRAM = 30
all: $(PROGRAM)

30: 30.o common.o
30.o: 30.cpp
common.o: common.cpp

## 適当
clean:
	rm -f $(PROGRAM) *.o
.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $<
%:
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIB)

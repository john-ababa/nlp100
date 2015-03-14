.PHONY: all clean
.SUFFIXES: .cpp .o

CXX = g++
CXXFLAGS = -O3 -Wall -Wextra -std=c++11
PROGRAM = 00 01 02 03
all: $(PROGRAM)

00: 00.o
00.o: 00.cpp
01: 01.o
01.o: 01.cpp
02: 02.o
02.o: 02.cpp
03: 03.o
03.o: 03.cpp

## 適当
clean:
	rm -f $(PROGRAM) *.o
.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $<
%:
	$(CXX) $(CXXFLAGS) -o $@ $^

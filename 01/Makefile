.PHONY: all clean
.SUFFIXES: .cpp .o

CXX = g++
CXXFLAGS = -O3 -Wall -Wextra -std=c++11
PROGRAM = 00 01 02 03 04 05 06 07 08
all: $(PROGRAM)

00: 00.o
00.o: 00.cpp
01: 01.o
01.o: 01.cpp
02: 02.o
02.o: 02.cpp
03: 03.o
03.o: 03.cpp
04: 04.o
04.o: 04.cpp
05: 05.o
05.o: 05.cpp
06: 06.o
06.o: 06.cpp
07: 07.o
07.o: 07.cpp
08: 08.o
08.o: 08.cpp

## 適当
clean:
	rm -f $(PROGRAM) *.o
.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $<
%:
	$(CXX) $(CXXFLAGS) -o $@ $^

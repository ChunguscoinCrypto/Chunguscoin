# Chunguscoin Wrapper by Shafil Alam

CXX=g++
CXXFLAGS=-g -Wall -MMD

main: main.o test.o console.o
	$(CXX) $(CXXFLAGS) -o chunguscoin main.o test.o console.o

main.o: main.cpp test.h console.h
	$(CXX) $(CXXFLAGS) -c main.cpp

test.o: test.h
console.o : console.h

clean :
	-rm *.o $(objects) chunguscoin
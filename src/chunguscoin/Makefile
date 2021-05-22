# Chunguscoin Wrapper by Shafil Alam

CXX=g++
CXXFLAGS=-g -Wall -MMD

main : main.o test.o console.o rpc.o blockchain.o util.o
	$(CXX) $(CXXFLAGS) -o chunguscoin main.o test.o console.o rpc.o blockchain.o util.o

main.o : main.cpp test.h console.h rpc.h blockchain.cpp util.h
	$(CXX) $(CXXFLAGS) -c main.cpp

test.o : test.h
console.o : console.h
rpc.o : rpc.h
blockchain.o : blockchain.cpp
util.o : util.h

clean :
	-rm *.o $(objects) chunguscoin
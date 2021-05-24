# Chunguscoin Wrapper by Shafil Alam

CXX=g++
CXXFLAGS=-g -Wall -MMD

main : main.o test.o console.o rpc.o blockchain.o util.o node.o exec.o
	$(CXX) $(CXXFLAGS) -o chunguscoin main.o test.o console.o rpc.o blockchain.o util.o node.o exec.o

main.o : main.cpp test.h console.h rpc.h blockchain.cpp util.h node.h exec.h
	$(CXX) $(CXXFLAGS) -c main.cpp

test.o : test.h
console.o : console.h
rpc.o : rpc.h
blockchain.o : blockchain.cpp
util.o : util.h
node.o : node.h
exec.o : exec.h

clean :
	-rm *.o $(objects) chunguscoin

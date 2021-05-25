# Chunguscoin Wrapper by Shafil Alam

CC = g++
CFLAGS = -g -Wall
TARGET = chunguscoin
DEPS = blockchain.h console.h exec.h node.h rpc.h util.h test.h
OBJ = main.o blockchain.o console.o exec.o node.o rpc.o util.o test.o
    
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
      
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
	cp $(TARGET) ../../build/$(TARGET)

clean:
	rm *.o $(objects) $(TARGET)
	rm ../../build/$(TARGET)
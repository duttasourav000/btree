OBJS = BTreeOperations.o BTree.o Helper.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

BTree: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o BTree

Helper.o: Helper.h Helper.cpp
	$(CC) $(CFLAGS) Helper.cpp

BTreeOperations.o: BTreeTypeDefinitions.h BTreeOperations.cpp
	$(CC) $(CFLAGS) BTreeOperations.cpp

BTree.o: Helper.h BTreeTypeDefinitions.h Helper.h
	$(CC) $(CFLAGS) BTree.cpp

clean:
	\rm *.o *~ BTree
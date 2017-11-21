SRC_DIR = src
INC_DIR = include
OBJS = BTreeOperations.o BTree.o Helper.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
SUBDIRS = src

BTree: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o treesearch

Helper.o: $(INC_DIR)/Helper.h
	$(CC) $(CFLAGS) $(SRC_DIR)/Helper.cpp

BTreeOperations.o: $(INC_DIR)/BTreeTypeDefinitions.h $(INC_DIR)/Helper.h
	$(CC) $(CFLAGS) $(SRC_DIR)/BTreeOperations.cpp

BTree.o: $(INC_DIR)/Helper.h $(INC_DIR)/BTreeTypeDefinitions.h
	$(CC) $(CFLAGS) $(SRC_DIR)/BTree.cpp

clean:
	\rm *.o *~ treesearch

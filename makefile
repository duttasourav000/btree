#EXE = treesearch
#
##SRC_DIR = src
#OBJ_DIR = obj
#INC_DIR = include
#
##SRC = $(wildcard $(SRC_DIR)/*.cpp)
#OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
#INC = -I$(INC_DIR)
#CPPFLAGS += -Iinclude
#CFLAGS += -Wall $(INC)
#LDFLAGS += -Llib
#LDLIBS += -lm
#
##.PHONY: all clean
#
##all: $(EXE)
#
##$(EXE): $(OBJ)
#       $(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
#       #
#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
#       $(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
#       #
#clean:
#       $(RM) $(OBJ)

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

Helper.o: $(SRC_DIR)/Helper.h $(SRC_DIR)/Helper.cpp
	$(CC) $(CFLAGS) $(SRC_DIR)/Helper.cpp

BTreeOperations.o: $(SRC_DIR)/BTreeTypeDefinitions.h $(SRC_DIR)/BTreeOperations.cpp
	$(CC) $(CFLAGS) $(SRC_DIR)/BTreeOperations.cpp

BTree.o: $(SRC_DIR)/Helper.h $(SRC_DIR)/BTreeTypeDefinitions.h $(SRC_DIR)/Helper.h
	$(CC) $(CFLAGS) $(SRC_DIR)/BTree.cpp

clean:
	\rm *.o treesearch

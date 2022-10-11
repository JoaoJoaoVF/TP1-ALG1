CC = g++
CFLAGS = -g -Wall -c -I$(INC) -std=c++11

LIBS = -lm 
SRC = src
OBJ = ./obj/
INC = ./include/
BIN = ./bin/
OBJS = $(OBJ)/2_sat.o $(OBJ)/main.o
HDRS = $(INC)/msgassert.hpp $(INC)/2_sat.hpp 

EXE = $(BIN)/tp1

all: run

run: $(EXE)
	$(EXE) tp1 

$(BIN)/tp1: $(OBJS)
	$(CC) -g -o $(BIN)/tp1 $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC)  $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp 

$(OBJ)/2_sat.o: $(HDRS) $(SRC)/2_sat.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/2_sat.o $(SRC)/2_sat.cpp 

clean:
	rm -f $(EXE)* $(OBJS)* $(BIN)* gmon.out
	clear   



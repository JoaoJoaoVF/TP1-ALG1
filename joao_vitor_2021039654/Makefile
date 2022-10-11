CC = g++
LIBS = -lm 
SRC = src
OBJ = ./obj/
INC = ./include/
BIN = ./bin/
OBJS = $(OBJ)/2_sat.o $(OBJ)/main.o
HDRS = $(INC)/2_sat.hpp $(INC)/msgassert.hpp
CFLAGS = -g -Wall -c -I$(INC)

EXE = $(BIN)/tp01

all: run

run: $(BIN)/tp01

exe: $(EXE)
	$(EXE) tp01 

$(BIN)/tp01: $(OBJS)
	$(CC) -g -o $(BIN)/tp01 $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC)  $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp 

$(OBJ)/2_sat.o: $(HDRS) $(SRC)/2_sat.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/2_sat.o $(SRC)/2_sat.cpp 

clean:
	rm -f $(EXE)* $(OBJS)* $(BIN)* 
	clear   
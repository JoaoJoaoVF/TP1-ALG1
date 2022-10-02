CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -Wall
LDFLAGS=-g
LDLIBS=

SRCS=main.cpp campanha.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: tp01

tp01: $(OBJS)
	$(CXX) $(LDFLAGS) -o tp01 $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

run:
	./tp01 < casoTeste01.txt

clean:
	$(RM) $(OBJS) tp01
	clear 

distclean: clean
	$(RM) *~ .depend tp01

#include .depend
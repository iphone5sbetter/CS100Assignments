# A simple makefile for CSE 100 P4

CC=g++
CXXFLAGS=-g -std=c++11
LDFLAGS=-g

all: bogtest

bogtest:  boggleplayer.o boggleutil.o

boggleplayer.o: boggleutil.h 	baseboggleplayer.h 	boggleplayer.h

boggleutil.o: boggleutil.h

clean:
	rm -f bogtest  *.o core*



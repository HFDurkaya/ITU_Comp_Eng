# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CC = g++
CFLAGS = -Wall -g

# ****************************************************
# Targets needed to bring the executable up to date

all: main clean

main: main.o RBTree.o
		$(CC) $(CFLAGS) -o homework3 main.o RBTree.o 

# The main.o target can be written more simply

main.o: main.cpp RBTree.h
		$(CC) $(CFLAGS) -c main.cpp 

RBTree.o: RBTree.h

clean:
		$(RM) *.o
                   
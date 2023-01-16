# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CC = g++
CFLAGS = -Wall -g

# ****************************************************
# Targets needed to bring the executable up to date

all: main clean

main: main.o 
		$(CC) $(CFLAGS) -I inc -o bin/main main.o 

# The main.o target can be written more simply

main.o: src/main.cpp include/funcs.h
		$(CC) $(CFLAGS) -c src/main.cpp -I include

clean:
		$(RM) *.o
                   
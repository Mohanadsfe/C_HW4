# Makefile for TCP project
.PHONY = all clean
CC=gcc
OBJS=algo.o  edges.o nodes.o main.o
EXEC=graph
DEBUG = -g
CFLAGS = -Wall -Werror $(DEBUG)

all : $(EXEC)
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)
q1.o: algo.c algo.h
	$(CC) $(CFLAGS) -c algo.c
q2.o: edges.c edges.h
	$(CC) $(CFLAGS) -c edges.c
q3.o: nodes.c nodes.h
	$(CC) $(CFLAGS) -c nodes.c
main.o: main.c algo.h edges.h nodes.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o *.a graph

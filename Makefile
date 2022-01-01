# Makefile for TCP project

all: graph

graph: main.c algo.c edges.c nodes.c
	gcc -Wall algo.c -o algo.o -c
	gcc -Wall edges.c -o edges.o -c
	gcc -Wall nodes.c -o nodes.o -c
	gcc -Wall main.c -o main.o -c
	gcc -Wall main.o edges.o nodes.o algo.o -o graph
	rm -f *.o

clean:
	rm -f *.o graph

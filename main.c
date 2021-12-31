#include <stdio.h>
#include <stdlib.h>

#include "edges.h"
#include "nodes.h"
#include "algo.h"

#define MAX_INPUT_SIZE 1 << 18

void parseInput(char* input);
int endOfCommand(char* input);
char* createNewGraph_A(char* input);
char* addNodeAndEdges_A(char* input);
char* addNodeAndEdges_B(char* input);
char* deleteNode_D(char* input);
char* shortestPath_S(char* input);
char* tsp_T(char* input);
int char2int(char c);

void deleteCurrentGraph();
void printGraph();

// this is the main function
// it allocates char array, gets input from user, parse the input and delete the graph that was created
int main()
{
    char* input = (char*) calloc(MAX_INPUT_SIZE, sizeof(char));

    scanf("%[^\n]s",input);

    parseInput(input);

    //printGraph();

    deleteCurrentGraph();

    free(input);
}

// this function parses the input, each iteration parses one command ('A', 'B', 'D', 'S', 'T')
void parseInput(char* input) {
    while (*input)
    {
        char command = *input;

        input += 2;
        if (command == 'A')
        {
            input = createNewGraph_A(input);
        }
        else if (command == 'B')
        {
            input = addNodeAndEdges_B(input);
        }
        else if (command == 'D')
        {
            input = deleteNode_D(input);
        }
        else if (command == 'S')
        {
            input = shortestPath_S(input);
        }
        else if (command == 'T')
        {
            input = tsp_T(input);
        }
    }
}


// parse the A command, build a graph with nodes and edges
char* createNewGraph_A(char* input) {
    int numberOfNodes = char2int(*input);
    int i;
    for (i = 0; i < numberOfNodes; i++) {
        addNode(i);
    }
    
    input+=2;

    while (!endOfCommand(input))
    {
        input = addNodeAndEdges_A(input);
    }
    return input;
}

// this function addes 1 node and edges from that node (FOR A COMMAND)

char* addNodeAndEdges_A(char* input) {
    input+=2; // skip 'n'
    int node_id = char2int(*input);
    input+=2; // skip id

    if (!doesNodeExists(node_id)) {
        addNode(node_id);
    }

    while (*input != 'n' && !endOfCommand(input))
    {
        int dest = char2int(*input);
        input+=2; // skip dest
        int weight = char2int(*input);
        input+=2; // skip weight
        addEdge(node_id, dest, weight);
    }

    return input;
}

// this function addes 1 node and edges from that node (FOR B COMMAND)
// if node already exists, deletes all the edges that exit from this node, before adding the new ones.
char* addNodeAndEdges_B(char* input) {
    int node_id = char2int(*input);
    if (!doesNodeExists(node_id))
    {
        addNode(node_id);
    }
    removeEdgesThatExitFrom(node_id);
    input+=2; // skip id

    while (!endOfCommand(input))
    {
        int dest = char2int(*input);
        input+=2; // skip dest
        int weight = char2int(*input);
        input+=2; // skip weight
        addEdge(node_id, dest, weight);
    }

    return input;
}

// deletes a node and all its edges
char* deleteNode_D(char* input) 
{
    int node_id = char2int(*input);

    deleteNode(node_id);
    removeEdgesThatExitTo(node_id);
    removeEdgesThatExitFrom(node_id);

    return input + 2;
}

// finds the shortests path between 2 nodes in a directed, weighted graph, using Dijsktra algorithm
char* shortestPath_S(char* input)
{
    int from = char2int(*input);
    input += 2;
    int to = char2int(*input);

    printf("Dijsktra shortest path: %d\n", dijsktra(from, to));

    return input + 2;
}

// finds the shortest path between k given nodes in a directed, weighted graph, using tsp algorithm
char* tsp_T(char* input)
{
    int k = char2int(*input);
    input+= 2;
    int nodes[6];
    int i;

    for (i = 0; i < 6; i++)
    {
        nodes[i] = -1;
    }

    for (i = 0; i < k; i++) {
        nodes[i] = char2int(*input);
        input += 2;
    }

    printf("TSP shortest path: %d\n", tsp(k, nodes));

    return input;
}


// checks if this is end of command char
int endOfCommand(char* input)
{
    char c = *input;

    if (c == (char)0 || c == 'A' || c == 'B' || c == 'D' || c == 'S' || c == 'T')
    {
        return 1;
    }

    return 0;
}


// casts char to int, '5' -> 5
int char2int(char c)
{
    return (int)(c - '0');
}

// deletes the current graph's node and edges
void deleteCurrentGraph() {
    deleteAllNodes();
    deleteAllEdges();
}

void printGraph() {
    printNodes();
    printEdges();
}


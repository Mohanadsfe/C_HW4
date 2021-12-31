
#include "edges.h"
#include <stdio.h>
#include <stdlib.h>

struct link_edge* list_edge_head = 0;


// adds edge to the graph by adding a link to the edges linked list
void addEdge(int from, int to, int weight)
{
    struct link_edge* new_link = (struct link_edge*)calloc(1, sizeof(struct link_edge));
    new_link->from = from;
    new_link->to = to;
    new_link->weight = weight;
    new_link->next = list_edge_head;
    new_link->prev = 0;
    if (list_edge_head) {
        list_edge_head->prev = new_link;
    }

    list_edge_head = new_link;
}

// removes all edges that exit from this node
void removeEdgesThatExitFrom(int from)
{
    struct link_edge* current = list_edge_head;
    while (current)
    {
        if(current->from == from) 
        {
            if (current == list_edge_head)
            {
                struct link_edge* toDelete = current;
                current = current->next;
                list_edge_head = current;
                if (list_edge_head) 
                {
                    list_edge_head->prev = 0;
                }

                free(toDelete);
            }
            else 
            {
                struct link_edge* toDelete = current;
                current = current->next;

                toDelete->prev->next = current;
                if (current) {
                    current->prev = toDelete->prev;
                }
                free(toDelete);
            }
        }
        else
        {
            current = current->next;
        }
    }
}

// removes all edges that exit to this node
void removeEdgesThatExitTo(int to)
{
    struct link_edge* current = list_edge_head;
    while (current)
    {
        if(current->to == to) 
        {
            if (current == list_edge_head)
            {
                struct link_edge* toDelete = current;
                current = current->next;
                list_edge_head = current;
                if (list_edge_head) 
                {
                    list_edge_head->prev = 0;
                }

                free(toDelete);
            }
            else 
            {
                struct link_edge* toDelete = current;
                current = current->next;

                toDelete->prev->next = current;
                if (current) {
                    current->prev = toDelete->prev;
                }
                free(toDelete);
            }
        }
        else
        {
            current = current->next;
        }
    }
}

// delets all the edges in the graph
void deleteAllEdges() {
    struct link_edge* current = list_edge_head;
    while (current) {
        struct link_edge* temp = current->next;
        free(current);
        current = temp;
    }
}

// prints the edges in the graph
void printEdges() {
    printf("all edges: ");
    struct link_edge* current = list_edge_head;
    while (current) {
        struct link_edge* temp = current->next;
        printf("(from: %d, to: %d, weight: %d) ", current->from, current->to, current->weight);
        current = temp;
    }

    printf("\n");
}

// given two nodes, return the weight of the edge (from, to), or INFINITY if there isn't such edge
int getWeight(int from, int to) {
    if (from == to){
        return 0;
    }

    struct link_edge* current = list_edge_head;
    while (current) {
        if (current->from == from && current->to == to) {
            return current->weight;
        }
        current = current->next;
    }

    return INFINITY;
}
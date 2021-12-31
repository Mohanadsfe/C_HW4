#include "nodes.h"
#include <stdio.h>
#include <stdlib.h>

struct link_node* list_node_head = 0;

// adds node to the graph by adding a link to the nodes linked list
void addNode(int node_id)
{
    struct link_node* new_link = (struct link_node*)calloc(1, sizeof(struct link_node));
    new_link->node_id = node_id;
    new_link->next = list_node_head;
    new_link->prev = 0;
    if (list_node_head)
    {
        list_node_head->prev = new_link;
    }
    list_node_head = new_link;
}

// removes node to the graph by removing a link from the nodes linked list
void deleteNode(int node_id)
{
    struct link_node* current = list_node_head;
    while (current)
    {
        if(current->node_id == node_id) 
        {
            if (current == list_node_head)
            {
                struct link_node* toDelete = current;
                current = current->next;
                list_node_head = current;
                if (list_node_head) 
                {
                    list_node_head->prev = 0;
                }

                free(toDelete);
            }
            else 
            {
                struct link_node* toDelete = current;
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

// checks if theres a node in the graph with a given node_id
int doesNodeExists(int node_id)
{
    struct link_node* current = list_node_head;
    while (current) {
        if (current->node_id == node_id)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// deletes all nodes
void deleteAllNodes() {
    struct link_node* current = list_node_head;
    while (current) {
        struct link_node* temp = current->next;
        free(current);
        current = temp;
    }
}

// prints all nodes
void printNodes() {
    printf("all nodes: ");
    struct link_node* current = list_node_head;
    while (current) {
        struct link_node* temp = current->next;
        printf("%d ", current->node_id);
        current = temp;
    }

    printf("\n");
}


// gets the node with max id
int getMaxNode() {
    int max = -1;

    struct link_node* current = list_node_head;
    while (current) {
        if(current->node_id > max) {
            max = current-> node_id;
        }
        current = current->next;
    }

    return max;
}
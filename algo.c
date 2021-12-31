#include <stdio.h>
#include <stdlib.h>

#include "edges.h"
#include "nodes.h"
#include "algo.h"

// runs the tsp algorithm
// each time we pick a different node "src" from "nodes", and recursively find the tsp in {nodes}\{src}, and take the min weight.
int tsp(int k, int* nodes) {
    int max_node = getMaxNode();
    if (max_node == -1){ // no nodes
        return max_node;
    }

    if (k < 2) {
        return 0;
    }

    int min_d = INFINITY;
    int i;
    for (i = 0; i < k; i++) {
        int src = nodes[i];
        int* new_nodes = new_list_without(k, src, nodes);
        int tsp_d = tsp_helper(max_node, k - 1, src, new_nodes);
        if (min_d > tsp_d) {
            min_d = tsp_d;
        }
        free(new_nodes);
    }

    if (min_d == INFINITY) {
        return -1;
    }
    return min_d;
}


// helper function for tsp
int tsp_helper(int max_node, int k, int src, int* nodes) {
  // if k = 1, simply run dijsktra
  if (k == 1) {
    struct dijsktra_result* res = dijsktra_helper(src, max_node);

    int dest = nodes[0];

    int result = res->distance[dest];

    free_dijsktra_result(res);

    return result;
  }

  // if k > 1, run dijsktra and take the min tsp from recursive calls
  int min_d = INFINITY;  
  int i;
  struct dijsktra_result* res = dijsktra_helper(src, max_node);
  for (i = 0; i < k; i++) {
    int dest = nodes[i];
    if (res->distance[dest] < INFINITY) {

        int* new_nodes = new_list_without(k, dest, nodes);
        int tsp_d = tsp_helper(max_node, k -1, dest, new_nodes);
        if(min_d > tsp_d + res->distance[dest]) {
            min_d = tsp_d + res->distance[dest];
        }
        free(new_nodes);
    }
  }

  free_dijsktra_result(res);
  
  return min_d;
}

// given a list "curr_list" of length k, returns a new list of lenth k-1, without the "without" element
int* new_list_without(int k, int without, int* curr_list) {
    int* new_list = (int*)calloc(k -1, sizeof(int));
    int i;
    int index = 0;

    for (i = 0; i < k; i++){
        if(curr_list[i] == without) {
            continue;
        }

        new_list[index] = curr_list[i];
        index++;
    }

    return new_list;
}

// runs dijsktra algorithm
int dijsktra(int src, int dest) {

    if (src == dest) {
        return 0;
    }

    int max_node = getMaxNode();
    if (max_node == -1){ // no nodes
        return max_node;
    }
    struct dijsktra_result* res = dijsktra_helper(src, max_node);

    int result = res->distance[dest];
    free_dijsktra_result(res);

    if (result == INFINITY) {
        return -1;
    }

    return result;
} 

// helper function for dijsktra
struct dijsktra_result* dijsktra_helper (int src, int max_node){

    int* visited = (int*)calloc(max_node + 1, sizeof(int));
    int* distance = (int*)calloc(max_node + 1, sizeof(int));

    int i;
    for (i = 0; i <= max_node; i++) {
        visited[i] = 0;
        distance[i] = getWeight(src, i);
    }

    visited[src] = 1;

    int count;
    for (count = 1; count <= max_node; count++) {
        int node = -1;
        int min_distance = INFINITY;

        for (i = 0; i <= max_node; i++) {
            if (distance[i] < min_distance && !visited[i]) {
                node = i;
                min_distance = distance[i];
            }
        }

        if (node == -1) {
            continue;
        }
        
        visited[node] = 1;

        for (i = 0; i <= max_node; i++){
            if (!visited[i]) {
                int w = getWeight(node, i);
                if (min_distance + w < distance[i]) {
                    distance[i]= min_distance + w;
                }
            }
        }
    }

    struct dijsktra_result* res = (struct dijsktra_result*)calloc(1, sizeof(struct dijsktra_result));

    res->distance = distance;
    res->visited = visited;

   return res;
}

void free_dijsktra_result(struct dijsktra_result* res) {
    free(res->distance);
    free(res->visited);
    free(res);
}
#ifndef ALGO_H_   
#define ALGO_H_

#endif // ALGO_H_

int dijsktra(int src, int dest);
int tsp(int k, int* nodes);
struct dijsktra_result* dijsktra_helper (int src, int max_node);
int tsp_helper(int max_node, int k, int src, int* nodes);
void free_dijsktra_result(struct dijsktra_result* res);
int* new_list_without(int k, int without, int* curr_list);
struct dijsktra_result {
    int* visited;
    int* distance;
};
#ifndef EDGE_H_   
#define EDGE_H_

#define INFINITY 1 << 23

struct link_edge {
    int from;
    int to;
    int weight;
    struct link_edge *prev;
    struct link_edge *next;
};

void printEdges();
void removeEdgesThatExitFrom(int from);
void removeEdgesThatExitTo(int to);
void addEdge(int from, int to, int weight);
void deleteAllEdges();
int getWeight(int from, int to);
#endif // EDGE_H_
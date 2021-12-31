#ifndef NODE_H_   
#define NODE_H_

struct link_node {
    int node_id;
    struct link_node *prev;
    struct link_node *next;
};

void addNode(int node_id);
void printNodes();
int doesNodeExists(int node_id);
void deleteAllNodes();
void deleteNode(int node_id);
int getMaxNode();
#endif // NODE_H_
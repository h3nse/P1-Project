#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_EDGES_PER_NODE 4


typedef struct edge {
    int nodeA; // The node the edge connects to or from.
    int nodeB; // -||-
    int length;
    int priority; // Possibly irrelevant.
    int isCleared;
} edge_t;

typedef struct node {
    edge_t edgesFromNodeArray[MAX_EDGES_PER_NODE]; // Array of edges going from a node.
} node_t;


/* FROM MAINFUNCS.C */
void run_program();

node_t* generate_graph(int amountOfNodes);

int* odd_nodes_array (node_t* arrayOfNodes, int amountOfNodes);

/* FROM CPP.C */
void test_print();
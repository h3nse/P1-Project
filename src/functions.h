#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_EDGES_PER_NODE 4

typedef struct node node_t;

typedef struct {
    node_t* nodeA; // The node the edge connects to or from.
    node_t* nodeB; // -||-
    int length;

    int isFeasible; // For Yaxiong 
    int numberOfTraversals; // For Yaxiong; f(i, j)
    int weight; // For Yaxiong; w(i, j)
    int extraCost; // For Yaxiong R(i, j)
    
    int priority; // Possibly irrelevant.
    int isCleared;
} edge_t;

struct node {
    edge_t edgesFromNode[MAX_EDGES_PER_NODE]; // Array of edges going from a node.
    edge_t edgesToNode[MAX_EDGES_PER_NODE];
    int amountOfEdges;
};


/* FROM MAINFUNCS.C */
void run_program();


node_t* generate_graph(int amountOfNodes);

int* odd_nodes_array(node_t* arrayOfNodes, int amountOfNodes);

/* FROM CPP.C */
void test_print();
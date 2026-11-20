#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_EDGES_PER_NODE 4
typedef struct node node_t;

typedef struct {
    node_t *nodeA; // The node the edge connects to or from.
    node_t *nodeB; // -||-
    int length; // The constant length of a node

    // For Yaxiong
    int yaxIsFeasible;
    int yaxNumberOfTraversals; // f(i, j)
    int yaxWeight; // w(i, j)
    int yaxExtraCost; // R(i, j)
    
    int priority; // Possibly irrelevant.
    int isCleared; // Very possibly irrelevant
} edge_t;

struct node {
    edge_t edgesFromNode[MAX_EDGES_PER_NODE]; // Array of edges going from a node.
    edge_t edgesToNode[MAX_EDGES_PER_NODE];
    node_t *parentNode; // For Dijkstras
    int isUsed; // Used for eularian tour intree
    int id;
    int balanced; // Used for Edmonds' and johnson's dcpp
    int amountOfEdges;
    int distanceFromSrc; // For Dijkstras
};


/* FROM MAINFUNCS.C */
void run_program();


node_t* generate_graph(int amountOfNodes);

int* odd_nodes_array(node_t* arrayOfNodes, int amountOfNodes);

/* FROM CPP.C */
void test_print();
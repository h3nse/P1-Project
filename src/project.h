#ifndef P1_PROJECT_H
#define P1_PROJECT_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX_EDGES_PER_NODE 4
typedef struct node node_t;

typedef struct {
    node_t *nodeFrom; // The node the edge connects to or from.
    node_t *nodeTo; // -||-
    int length; // The constant length of a node

    // For Yaxiong
    int yaxIsFeasible;
    int yaxNumberOfTraversals; // f(i, j)
    int yaxWeight; // w(i, j)
    int yaxExtraCost; // R(i, j)
    int inTreeLabels; // Used for eulerian tour

    int priority; // Possibly irrelevant.
    int isCleared; // Very possibly irrelevant
} edge_t;

struct node {
    edge_t edgesFromNode[MAX_EDGES_PER_NODE]; // Array of edges going from a node.
    edge_t edgesToNode[MAX_EDGES_PER_NODE];
    node_t *parentNode; // For Dijkstras
    int isUsed; // Used for eulerian tour intree
    int id;
    int balanced; // Used for Edmonds' and johnson's dcpp
    int amountOfEdgesFromNode;
    int amountOfEdgesToNode; // Used in eulerian tour intree
    int distanceFromSrc; // For Dijkstras
};


/* FROM MAINFUNCS.C */
void run_program();

//node_t* generate_graph(int amountOfNodes);

int* odd_nodes_array(node_t* arrayOfNodes, int amountOfNodes);

/* FROM CPP.C */
void test_print();

#endif // P1_PROJECT_H